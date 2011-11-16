//
// C++ Interface: BaseDlg
//
// Description: 
//
//
// Author: root <root@andLinux>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef BASEDLG_H
#define BASEDLG_H

#include "GUI_Define.h"
#include <ZKbMainWidget.h>

#ifdef EZX_ZN5
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
    int result() const { return rescode; }
    
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
