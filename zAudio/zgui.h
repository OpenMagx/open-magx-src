//
// Poject name: zAudio
//
// Version: 0.1
//
// Description: Programm for change audio settings
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//

#ifndef ZGUI_H
#define ZGUI_H

#include "GUI_Define.h"

#include <qobject.h>
#include <unistd.h>

#include "gainDef.h"

#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZNavTabWidget.h>
#include <ZComboBox.h>

static QString ProgDir;

class ZGui : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZGui (QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    QString getProgramDir();
    void CreateWindow(QWidget* parent);
    
    void readFile();
    void updateView();
    
  public slots:
    void save();
    void slotChangeEqHP( int );
    void slotChangeEqSP( int );
    void slotChangeMenu( int );
        
  private:
    ZListBox * lbMedia;
    ZListBox * lbAlarm;

    ZListBox * lbEqHP;
    ZListBox * lbEqSP;
    
	ZListBox * lbMenu;
 
	ZComboBox * cbEgHPlist;
	ZComboBox * cbEgSPlist;
 
    ZListBox * lbDevice[ GAIN_DEVICE_COUNT + 2 ];
    
    ZNavTabWidget * tabWidget;
    
    char * gainTable;
    int tableLen;
};

#endif

