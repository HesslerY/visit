// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ************************************************************************* //
//                         avtMomentOfInertiaQuery.C                         //
// ************************************************************************* //

#include <avtMomentOfInertiaQuery.h>

#include <vtkCell.h>

#ifdef PARALLEL
#include <mpi.h>
#endif

#include <vtkCellData.h>
#include <vtkDataArray.h>
#include <vtkDataSet.h>
#include <vtkVisItUtility.h>

#include <avtAbsValExpression.h>
#include <avtBinaryMultiplyExpression.h>
#include <avtCallback.h>
#include <avtParallel.h>
#include <avtSourceFromAVTDataset.h>
#include <avtVMetricVolume.h>

#include <DebugStream.h>
#include <ImproperUseException.h>
#include <NonQueryableInputException.h>

#include <float.h>
#include <math.h>

using     std::string;
using     std::vector;

#if !defined(M_PI)
#define M_PI 3.14159265358979323846
#endif

// ****************************************************************************
//  Method: avtMomentOfInertiaQuery constructor
//
//  Programmer: Hank Childs
//  Creation:   May 17, 2005
//
//  Modifications:
//
//    Hank Childs, Fri Aug 12 15:30:59 PDT 2005
//    Added absval.
//
// ****************************************************************************

avtMomentOfInertiaQuery::avtMomentOfInertiaQuery()
{
    absval = new avtAbsValExpression;
    multiply = new avtBinaryMultiplyExpression;
    volume = new avtVMetricVolume;
}


// ****************************************************************************
//  Method: avtMomentOfInertiaQuery destructor
//
//  Purpose:
//      Defines the destructor.  Note: this should not be inlined in the header
//      because it causes problems for certain compilers.
//
//  Programmer: Hank Childs
//  Creation:   May 17, 2005
//
//  Modifications:
//
//    Hank Childs, Fri Aug 12 15:30:59 PDT 2005
//    Added absval.
//
// ****************************************************************************

avtMomentOfInertiaQuery::~avtMomentOfInertiaQuery()
{
    delete absval;
    delete multiply;
    delete volume;
}


// ****************************************************************************
//  Method: avtMomentOfInertiaQuery::VerifyInput
//
//  Purpose:
//    Rejects non-queryable input && input that has topological dimension == 0
//
//  Programmer: Hank Childs
//  Creation:   May 17, 2005
//
//  Modifications:
//
// ****************************************************************************

void
avtMomentOfInertiaQuery::VerifyInput()
{
    avtDataObjectQuery::VerifyInput();
    if (GetInput()->GetInfo().GetAttributes().GetTopologicalDimension() != 3)
    {
        EXCEPTION1(NonQueryableInputException,
            "VisIt can only calculate moment of inertia tensor for 3D plots."
            "  2D plots can be revolved into 3D for this query.");
    }
}


// ****************************************************************************
//  Method: avtMomentOfInertiaQuery::PreExecute
//
//  Purpose:
//      This is called before all of the domains are executed.
//
//  Programmer: Hank Childs
//  Creation:   May 17, 2005
//
//  Modifications:
//    Jeremy Meredith, Thu Feb 15 11:55:03 EST 2007
//    Call inherited PreExecute before everything else.
//
// ****************************************************************************

void
avtMomentOfInertiaQuery::PreExecute(void)
{
    avtDatasetQuery::PreExecute();

    for (int i = 0 ; i < 9 ; i++)
        I[i] = 0.;
}

// ****************************************************************************
//  Method: avtMomentOfInertiaQuery::PostExecute
//
//  Purpose:
//      This is called after all of the domains are executed.
//
//  Programmer: Hank Childs
//  Creation:   May 17, 2005
//
//  Modifications:
//
//    Cyrus Harrison, Tue Sep 18 13:45:35 PDT 2007
//    Added support for user settable floating point format string
//
//    Kathleen Biagas, Mon Feb 24 15:53:41 PST 2014
//    Add Xml results.
//
// ****************************************************************************

void
avtMomentOfInertiaQuery::PostExecute(void)
{
    double I_tmp[9];
    SumDoubleArrayAcrossAllProcessors(I, I_tmp, 9);

    //
    //  Parent class uses this message to set the Results message
    //  in the Query Attributes that is sent back to the viewer.
    //  That is all that is required of this query.
    //
    char msg[4096];
    string floatFormat = queryAtts.GetFloatFormat();
    string format = "Moment of inertia tensor = \n("
                      + floatFormat + ",\t" 
                      + floatFormat + ",\t" 
                      + floatFormat + ")\n(" 
                      + floatFormat + ",\t" 
                      + floatFormat + ",\t" 
                      + floatFormat + ")\n("
                      + floatFormat + ",\t" 
                      + floatFormat + ",\t" 
                      + floatFormat + ")\n";
                    
    snprintf(msg, 4096,format.c_str(),
             I_tmp[0], I_tmp[1], I_tmp[2], 
             I_tmp[3], I_tmp[4], I_tmp[5], 
             I_tmp[6], I_tmp[7], I_tmp[8]);
    SetResultMessage(msg);
    doubleVector I_vec(9);
    for (int i = 0 ; i < 9 ; i++)
        I_vec[i] = I_tmp[i];
    SetResultValues(I_vec);
    MapNode result_node;
    result_node["moment_of_inertia"] = I_vec;
    SetXmlResult(result_node.ToXML());
}

// ****************************************************************************
//  Method: avtMomentOfInertiaQuery::Execute
//
//  Purpose:
//      Processes a single domain.
//
//  Programmer: Hank Childs
//  Creation:   May 17, 2005
//
// ****************************************************************************

void
avtMomentOfInertiaQuery::Execute(vtkDataSet *ds, const int dom)
{
    vtkIdType nCells = ds->GetNumberOfCells();
    vtkDataArray *ghosts = ds->GetCellData()->GetArray("avtGhostZones");
    vtkDataArray *var = ds->GetCellData()->GetArray("avt_mass");
    if (var == NULL)
    {
        EXCEPTION0(ImproperUseException);
    }
    for (vtkIdType i = 0 ; i < nCells ; i++)
    {
        if (ghosts != NULL && ghosts->GetTuple1(i) != 0.)
            continue;
        vtkCell *cell = ds->GetCell(i);
        double center[3];
        vtkVisItUtility::GetCellCenter(cell, center);
        float mass = var->GetTuple1(i);
        I[0] += mass*(center[1]*center[1] + center[2]*center[2]);
        I[1] += -mass*center[0]*center[1];
        I[2] += -mass*center[0]*center[2];
        I[3] += -mass*center[0]*center[1];
        I[4] += mass*(center[0]*center[0] + center[2]*center[2]);
        I[5] += -mass*center[1]*center[2];
        I[6] += -mass*center[0]*center[2];
        I[7] += -mass*center[1]*center[2];
        I[8] += mass*(center[0]*center[0] + center[1]*center[1]);
    }
}


// ****************************************************************************
//  Method: avtMomentOfInertiaQuery::ApplyFilters
//
//  Purpose:
//      Applies the filters to the input.
//
//  Programmer: Hank Childs
//  Creation:   May 18, 2005
//
//  Modifications:
//
//    Hank Childs, Fri Aug 12 15:30:59 PDT 2005
//    Added absval.
//
//    Kathleen Bonnell, Wed Apr  2 10:20:27 PDT 2008 
//    Retrieve the varname from the queryAtts instead of DataRequest, as
//    DataRequest may have the wrong value based on other pipelines sharing
//    the same source. 
//
// ****************************************************************************

avtDataObject_p
avtMomentOfInertiaQuery::ApplyFilters(avtDataObject_p inData)
{
    //
    // Create an artificial pipeline.
    //
    avtDataset_p ds;
    CopyTo(ds, inData);
    avtSourceFromAVTDataset termsrc(ds);
    avtDataObject_p dob = termsrc.GetOutput();

    //
    // Set up our base class so it is ready to sum.
    //
    string varname = queryAtts.GetVariables()[0];
    bool useVar = false;
    if (GetInput()->GetInfo().GetAttributes().ValidVariable(varname))
    {
        int dim = GetInput()->GetInfo().GetAttributes().
                                         GetVariableDimension(varname.c_str());
        if (dim == 1)
            useVar = true;
    }

    volume->SetOutputVariableName("avt_verdict");
    volume->SetInput(dob);

    if (useVar)
        absval->SetOutputVariableName("avt_weights");
    else
        absval->SetOutputVariableName("avt_mass");
    absval->AddInputVariableName("avt_verdict");
    absval->SetInput(volume->GetOutput());
    dob = absval->GetOutput();
 
    if (useVar)
    {
        multiply->SetInput(dob);
        multiply->ClearInputVariableNames();
        multiply->AddInputVariableName(varname.c_str());
        multiply->AddInputVariableName("avt_weights");
        multiply->SetOutputVariableName("avt_mass");
        dob = multiply->GetOutput();
    }

    //
    // Cause our artificial pipeline to execute.
    //
    avtContract_p contract =
        inData->GetOriginatingSource()->GetGeneralContract();
    dob->Update(contract);
    return dob;
}


