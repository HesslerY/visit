// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef LINEARTRANSFORMATTRIBUTES_H
#define LINEARTRANSFORMATTRIBUTES_H
#include <state_exports.h>
#include <AttributeSubject.h>


// ****************************************************************************
// Class: LinearTransformAttributes
//
// Purpose:
//    This class contains attributes for the linear transform.
//
// Notes:      Autogenerated by xml2atts.
//
// Programmer: xml2atts
// Creation:   omitted
//
// Modifications:
//
// ****************************************************************************

class STATE_API LinearTransformAttributes : public AttributeSubject
{
public:
    // These constructors are for objects of this class
    LinearTransformAttributes();
    LinearTransformAttributes(const LinearTransformAttributes &obj);
protected:
    // These constructors are for objects derived from this class
    LinearTransformAttributes(private_tmfs_t tmfs);
    LinearTransformAttributes(const LinearTransformAttributes &obj, private_tmfs_t tmfs);
public:
    virtual ~LinearTransformAttributes();

    virtual LinearTransformAttributes& operator = (const LinearTransformAttributes &obj);
    virtual bool operator == (const LinearTransformAttributes &obj) const;
    virtual bool operator != (const LinearTransformAttributes &obj) const;
private:
    void Init();
    void Copy(const LinearTransformAttributes &obj);
public:

    virtual const std::string TypeName() const;
    virtual bool CopyAttributes(const AttributeGroup *);
    virtual AttributeSubject *CreateCompatible(const std::string &) const;
    virtual AttributeSubject *NewInstance(bool) const;

    // Property selection methods
    virtual void SelectAll();

    // Property setting methods
    void SetM00(double m00_);
    void SetM01(double m01_);
    void SetM02(double m02_);
    void SetM03(double m03_);
    void SetM10(double m10_);
    void SetM11(double m11_);
    void SetM12(double m12_);
    void SetM13(double m13_);
    void SetM20(double m20_);
    void SetM21(double m21_);
    void SetM22(double m22_);
    void SetM23(double m23_);
    void SetM30(double m30_);
    void SetM31(double m31_);
    void SetM32(double m32_);
    void SetM33(double m33_);
    void SetInvertLinearTransform(bool invertLinearTransform_);
    void SetTransformVectors(bool transformVectors_);

    // Property getting methods
    double GetM00() const;
    double GetM01() const;
    double GetM02() const;
    double GetM03() const;
    double GetM10() const;
    double GetM11() const;
    double GetM12() const;
    double GetM13() const;
    double GetM20() const;
    double GetM21() const;
    double GetM22() const;
    double GetM23() const;
    double GetM30() const;
    double GetM31() const;
    double GetM32() const;
    double GetM33() const;
    bool   GetInvertLinearTransform() const;
    bool   GetTransformVectors() const;

    // Persistence methods
    virtual bool CreateNode(DataNode *node, bool completeSave, bool forceAdd);
    virtual void SetFromNode(DataNode *node);


    // Keyframing methods
    virtual std::string               GetFieldName(int index) const;
    virtual AttributeGroup::FieldType GetFieldType(int index) const;
    virtual std::string               GetFieldTypeName(int index) const;
    virtual bool                      FieldsEqual(int index, const AttributeGroup *rhs) const;


    // IDs that can be used to identify fields in case statements
    enum {
        ID_m00 = 0,
        ID_m01,
        ID_m02,
        ID_m03,
        ID_m10,
        ID_m11,
        ID_m12,
        ID_m13,
        ID_m20,
        ID_m21,
        ID_m22,
        ID_m23,
        ID_m30,
        ID_m31,
        ID_m32,
        ID_m33,
        ID_invertLinearTransform,
        ID_transformVectors,
        ID__LAST
    };

private:
    double m00;
    double m01;
    double m02;
    double m03;
    double m10;
    double m11;
    double m12;
    double m13;
    double m20;
    double m21;
    double m22;
    double m23;
    double m30;
    double m31;
    double m32;
    double m33;
    bool   invertLinearTransform;
    bool   transformVectors;

    // Static class format string for type map.
    static const char *TypeMapFormatString;
    static const private_tmfs_t TmfsStruct;
};
#define LINEARTRANSFORMATTRIBUTES_TMFS "ddddddddddddddddbb"

#endif
