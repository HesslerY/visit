/*****************************************************************************
*
* Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//                            avtSASFileFormat.h                             //
// ************************************************************************* //

#ifndef AVT_SAS_FILE_FORMAT_H
#define AVT_SAS_FILE_FORMAT_H

#include <avtMTMDFileFormat.h>

#ifdef WIN32
#include <io.h>
#define OPEN    ::_open
#define CLOSE   ::_close
#define READ    ::_read
#define WRITE   ::_write
#define LSEEK64 ::_lseeki64
#define OFF64_T ::__int64
#define ssize_t int

#else
#include <unistd.h>

#define O_BINARY 0
#define OPEN  ::open
#define CLOSE ::close
#define READ  ::read
#define WRITE ::write
#if defined(__APPLE__) || defined(_OSF_SOURCE)
#define LSEEK64 ::lseek
#define OFF64_T ::off_t
#else
#define LSEEK64 ::lseek64
#define OFF64_T ::off64_t
#endif

#endif

#include <vector>
class vtkUnstructuredGrid;
struct AssemblyType;
struct Assembly
{
    int                  iDomain;
    vtkUnstructuredGrid *grid;
};

// ****************************************************************************
//  Class: avtSASFileFormat
//
//  Purpose:
//      Reads in SAS files as a plugin to VisIt.
//
//  Programmer: dbremer -- generated by xml2avt
//  Creation:   Wed Jul 18 12:38:36 PDT 2007
//
//  Modifications:
//    David Bremer, Sep 7, 2007
//    Added GetCycles call.  The data doesn't contain cycle metadata, but 
//    returning it here has the nice side effect of making the query over time 
//    and pick over time do the right thing by default.
//
//    Hank Childs, Sun Oct 21 09:34:21 PDT 2007
//    Change stdint.h to inttypes.h for portability on suns.
//
// ****************************************************************************

class avtSASFileFormat : public avtMTMDFileFormat
{
  public:
                           avtSASFileFormat(const char *);
    virtual               ~avtSASFileFormat();

    virtual void           GetTimes(std::vector<double> &);
    virtual void           GetCycles(std::vector<int> &);

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "SAS"; }
    virtual void           FreeUpResources(void); 

    virtual vtkDataSet    *GetMesh(int, int, const char *);
    virtual vtkDataArray  *GetVar(int, int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, int, const char *);

  protected:
    std::string            geomFileName;
    std::string            dataFileName;
    bool                   bDataFileIsMissing; // In this case, only draw the mesh
    bool                   bSwapEndian;

    int                    nAssemblyTypes;
    AssemblyType          *aAssemblyTypes;
    int                    nAssemblys;
    OFF64_T                iAssemblyDiskLoc;   //location of first assembly

    std::vector<Assembly>  aCachedAssemblies;

    std::vector<double>    aTimes;
    int                    nChannels;          //number of channels written into each timestep
    int                   *aChannels;          //array of tuples [global channel id, num elements, filepos of data]
    int                    iTimeStepSize;      //disk size of each timestep, in bytes

    enum { NO_CHANNELS,
           UNSORTED_CHANNELS,
           SORTED_CHANNELS,
           SEQUENTIAL_CHANNELS } eChannelOrder;
    int                    iFirstChannel;     //used only if eChannelOrder==SEQUENTIAL_CHANNELS

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);
    virtual void           ReadAssemblyTypes();
    virtual void           ReadTimeStepData();
    virtual bool           FindChannel(int globalChannelID, int *length, int *fileoffset);

    int                    ReadInt(int f);
    void                   ReadDoubleArray(int f, double *array, int num);
    std::string            ReadFortranString(int f);

    static void            ByteSwap32(void *aVals, int nVals);
    static void            ByteSwap64(void *aVals, int nVals);
};



// ****************************************************************************
//  Class: AssemblyType
//
//  Purpose:
//      Defines a mesh, or "assembly", which can be instanced several times
//      within a dataset.  Each assembly is composed of channels, which are
//      stacks of wedge or hex cells along the z axis.  Channels model the 
//      empty space between rods in a reactor core.
//
//  Programmer: David Bremer
//  Creation:   Mon Jul 30 19:38:14 PDT 2007
//
// ****************************************************************************

struct AssemblyType
{
    AssemblyType();
    virtual ~AssemblyType();

    int     id;            // Assembly type id
    int     nChannels;     
    int    *aChannelIDs;   // These are in a local space.
    int     nZVals;
    double *aZVals;        // z coords

    int     nUniquePts;
    double *aUniquePts;    // List of unique xy points
    int    *aChannelSizes; // Either 3 or 4.  Num points in base of channel
    int    *aChannelPts;   // Indices into aXYPts.  4 elements alloced for each channel.
};





#endif
