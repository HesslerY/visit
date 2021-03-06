// Copyright (c) Lawrence Livermore National Security, LLC and other VisIt
// Project developers.  See the top-level LICENSE file for dates and other
// details.  No copyright assignment is required to contribute to VisIt.

#ifndef QVISSUBDIVIDEQUADSWINDOW_H
#define QVISSUBDIVIDEQUADSWINDOW_H

#include <QvisOperatorWindow.h>
#include <AttributeSubject.h>

class SubdivideQuadsAttributes;
class QLabel;
class QCheckBox;
class QLineEdit;
class QvisVariableButton;

// ****************************************************************************
// Class: QvisSubdivideQuadsWindow
//
// Purpose:
//    Defines QvisSubdivideQuadsWindow class.
//
// Notes:      Autogenerated by xml2window.
//
// Programmer: xml2window
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

class QvisSubdivideQuadsWindow : public QvisOperatorWindow
{
    Q_OBJECT
  public:
    QvisSubdivideQuadsWindow(const int type,
                         SubdivideQuadsAttributes *subj,
                         const QString &caption = QString(),
                         const QString &shortName = QString(),
                         QvisNotepadArea *notepad = 0);
    virtual ~QvisSubdivideQuadsWindow();
    virtual void CreateWindowContents();
  protected:
    void UpdateWindow(bool doAll);
    virtual void GetCurrentValues(int which_widget);
  private slots:
    void thresholdProcessText();
    void maxSubdivsProcessText();
    void fanOutPointsChanged(bool val);
    void doTrianglesChanged(bool val);
    void variableChanged(const QString &varName);
  private:
    QLineEdit *threshold;
    QLineEdit *maxSubdivs;
    QCheckBox *fanOutPoints;
    QCheckBox *doTriangles;
    QvisVariableButton *variable;
    QLabel *thresholdLabel;
    QLabel *maxSubdivsLabel;
    QLabel *variableLabel;

    SubdivideQuadsAttributes *atts;
};



#endif
