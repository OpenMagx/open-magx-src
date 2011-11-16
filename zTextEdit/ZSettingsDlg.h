//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef ZSETTINGSDLG_H
#define ZSETTINGSDLG_H

#include "GUI_Define.h"
#include "BaseDlg.h"
#include <ZMessageDlg.h>
#include <ZListBox.h>
#if !( defined(EZX_Z6) || defined(EZX_V8) )
#include <ZSettingItem.h>
#endif


class ZSettingsDlg : public MyBaseDlg {
  Q_OBJECT

  public:
    ZSettingsDlg(); 
    ~ZSettingsDlg();

  public slots:
    void slot_chengeOption(int);

  private:
	ZListBox * lbOptions;
	ZSettingItem * ziFontSize;
	ZSettingItem * ziUnderline;
	ZSettingItem * ziAutoOpen;
	ZSettingItem * ziMenuDial;
	ZSettingItem * ziChineseCodeDetect;
	ZSettingItem * ziSelCurLine;
	/*
	#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )
	ZSettingItem * ziInfoBar;
	#endif
	*/
	
	int cfg_fontSize;
	bool cfg_underline;
	bool cfg_autoOpen;
	bool cfg_menuCopy;
	bool cfg_chineseCodeDetect;
	bool cfg_selCurLine;
	/*
	#if !( defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W) )
	bool cfg_infoBar;
	#endif
    */
    
  protected:
    virtual void accept();     
};

#endif
