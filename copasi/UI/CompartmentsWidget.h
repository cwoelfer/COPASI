/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget, i.e the First level 
 ** of Compartments.
 *****************************************************************************/

#ifndef COMPARTMENTS_WIDGET_H
#define COMPARTMENTS_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h>
#include "MyTable.h"
#include "copasi.h"
#include "model/model.h"

class CModel;

class CompartmentsWidget : public QWidget
  {
    Q_OBJECT

  protected:
    CModel *mModel;
    MyTable *table;
    QPushButton *btnOK;
    QPushButton *btnCancel;

  public:
    CompartmentsWidget(QWidget *parent, const char * name = 0, WFlags f = 0);
    void loadCompartments(CModel *model);
    //void mousePressEvent(QMouseEvent * e);
    void resizeEvent(QResizeEvent * re);

  public slots:
    virtual void slotTableCurrentChanged(int, int, int, const QPoint &);

  signals:
    void name(QString &);

  protected slots:

    virtual void slotTableSelectionChanged();
    virtual void slotBtnOKClicked();
    virtual void slotBtnCancelClicked();

  private:
    void showMessage(QString caption, QString text);
  };

#endif
