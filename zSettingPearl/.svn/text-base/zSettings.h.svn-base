//
// C++ Implementation: ZSettigs
//
// Description:
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2011
//
// Based on zSimpleGUI by BeZ
//

#ifndef ZGUI_H
#define ZGUI_H

#include <qobject.h>
#include <unistd.h>
#include <stdlib.h>

#include <ZMessageDlg.h>
#include <ZComboBox.h>
#include <ZKbMainWidget.h>
#include <ZNavTabWidget.h>
#include <ZListBox.h>

#include "ZOptionItem.h"
#include "BaseDlg.h"

class ZSettigs : public MyBaseDlg
{
    Q_OBJECT
  public:
    ZSettigs (QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZSettigs();
      
    QString getProgramDir();
    QString ProgDir;
    void CreateWindow(QWidget* parent);  
    void toLog(QString mes, bool r1 = false , bool r2 = false );

  public slots:
    void save();
    void applySetting(int);
	
  private:
  	ZNavTabWidget *tabWidget;
    ZSoftKey *softKey;
    
    ZListBox * lbSysOption;
    ZListBox * lbToolOption;
    ZListBox * lbSoundOption;
    ZListBox * lbKeyOption;    
    ZListBox * lbService;    
};

extern "C" int GetFlexIdByName(char *);

#endif
