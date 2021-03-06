// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

// ****************************************************************************
//  File: AxisAlignedSlice4DGUIPluginInfo.C
// ****************************************************************************

#include <AxisAlignedSlice4DPluginInfo.h>
#include <AxisAlignedSlice4DAttributes.h>
#include <QApplication>
#include <QvisAxisAlignedSlice4DWindow.h>

VISIT_OPERATOR_PLUGIN_ENTRY(AxisAlignedSlice4D,GUI)

// ****************************************************************************
//  Method: AxisAlignedSlice4DGUIPluginInfo::GetMenuName
//
//  Purpose:
//    Return a pointer to the name to use in the GUI menu.
//
//  Returns:    A pointer to the name to use in the GUI menu.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

QString *
AxisAlignedSlice4DGUIPluginInfo::GetMenuName() const
{
    return new QString(qApp->translate("OperatorNames", "Axis Aligned Slice 4D"));
}


// ****************************************************************************
//  Method: AxisAlignedSlice4DGUIPluginInfo::CreatePluginWindow
//
//  Purpose:
//    Return a pointer to an operator's attribute window.
//
//  Arguments:
//    type      The type of the operator.
//    attr      The attribute subject for the operator.
//    notepad   The notepad to use for posting the window.
//
//  Returns:    A pointer to the operator's attribute window.
//
//  Programmer: generated by xml2info
//  Creation:   omitted
//
// ****************************************************************************

QvisPostableWindowObserver *
AxisAlignedSlice4DGUIPluginInfo::CreatePluginWindow(int type, AttributeSubject *attr,
    const QString &caption, const QString &shortName, QvisNotepadArea *notepad)
{
    return new QvisAxisAlignedSlice4DWindow(type, (AxisAlignedSlice4DAttributes *)attr,
        caption, shortName, notepad);
}

