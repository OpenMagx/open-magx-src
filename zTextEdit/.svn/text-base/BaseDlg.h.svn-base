//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef BASEDLG_H
#define BASEDLG_H

#include "GUI_Define.h"
#include <ZKbMainWidget.h>

#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
#define _ZKbMainWidget ZMainWidget
#else
#define _ZKbMainWidget ZKbMainWidget
#endif

class MyBaseDlg : public _ZKbMainWidget 
{
  Q_OBJECT

  public:
    MyBaseDlg(); 
    ~MyBaseDlg();
    
    int exec();
    int result() const { return rescode; };
    #if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
    bool setMainWidgetTitle( const QString &Title );
    bool setSoftKey( ZSoftKey *cstWidget );
    QSize headerSize();
    #endif
    
  protected slots:
    virtual void done(int);
    virtual void accept();
    virtual void reject();
        
  private:
    bool myInLoop;
    int rescode;
    ZHeader * header;
        
  protected:
    enum DialogCode { Rejected, Accepted };
    void setResult(int r) { rescode = r; }    
};

#endif
