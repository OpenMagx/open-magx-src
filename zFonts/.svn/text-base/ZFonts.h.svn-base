//
// C++ Interface: ZFonts
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef ZFonts_H
#define ZFonts_H

#include "GUI_Define.h"

#include <ZKbMainWidget.h>
#include <ZListBox.h>

class ZFonts : public ZKbMainWidget
{
    Q_OBJECT
  public:
    ZFonts (QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZFonts();
    QString getProgramDir();
    void CreateWindow(QWidget* parent);
    
    QString getViewText();
    
    void fillFonts();
    void fillFontsByDir(QString sDir);
    
    void previewFont(QString sFontPath);
    
  public slots:
    void slot_about();
    void slot_preview();
    void slot_install();
    void slot_fontSelect(int);
    
  private:
    QString ProgDir;

	ZListBox * lbFonts;
    
	QString sViewText;
};



#endif

