//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef ZGUI_H
#define ZGUI_H

//My
#include "GUI_Define.h"
#include "BaseDlg.h"

//C++/C
#include <unistd.h>
#include <stdlib.h>

//QT
#include <qobject.h>
#include <qtextcodec.h>

//EZX
#include <ZMessageDlg.h>
#include <ZKbMainWidget.h>
#include <ZListBox.h>
#include <ZScrollPanel.h>
#include <ZOptionsMenu.h>
#include <ZMultiLineEdit.h>
#ifdef MDI
#include <qwidgetstack.h>
#endif

class ZGui : public MyBaseDlg
{
    Q_OBJECT
  public:
    ZGui (QWidget* parent = 0, const char* name = 0, WFlags fl = 0 );
    ~ZGui();
    
    QString getProgramDir();
    QString getFileName(const QString &AFileName);
    QString getFilePath(const QString &AFileName);
    
    void CreateWindow(QWidget* parent);
    
    QTextCodec* codecByLocalId( int id );
    int big5HeuristicContentMatch(const char* chars, int len);
    int checkCodec(char* chars, int len, int codeId);
    int detectCodec( char * chars, int maxLen = -1 );
    
    void load(const QString fileName, bool AutoCodec = true);
    void saveAs(const QString sFileName, bool save = false);
    
    void setSettingToEdit(ZMultiLineEdit * edit);
    
    #if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
    QString getSelectText();
    bool isSelectText();
    #endif
    
	int cfg_fontSize;
	bool cfg_underline; 
	bool cfg_infoBar; 
	bool cfg_autoOpen;   
	bool cfg_menuCopy;
	bool cfg_chineseCodeDetect;
	#ifdef SELECT_CUR_LINE
	bool cfg_selCurLine;
	#endif
    
  public slots:
    void slot_about();
    void slot_settings(); 
    void slot_exit();
    
    void slot_fileNew();
    void slot_fileOpen();
    void slot_fileSave();
    void slot_fileSaveAs();
    void slot_fileFind();
    
    void slot_editCopy();  
    void slot_editPaste(); 
    void slot_editCut(); 
	void slot_editSelectBlock();
    void slot_editSelAll();     
    
    void slot_codecChenged(int); 
    
    void slot_Raise();
    void slot_ReturnToIdle( int reason ); 
    
    void slot_minimize();   
    #ifdef MDI
    void slot_newDlg();
    void slot_nextDlg();
    void slot_dlgChenged(int); 
    void slot_closeDlg();
    #else
    void slot_newDlg(){};
    void slot_nextDlg(){};
    void slot_dlgChenged(int){}; 
    void slot_closeDlg(){};
    #endif
     
  protected:
    virtual bool eventFilter( QObject *target, QEvent *e );   
    
  private:
    QString ProgDir;
    
    #ifndef MDI
    
    #define MAX_DIALOG_COUNT 1
    ZMultiLineEdit * edit; 
    QString sFileName, sFilePath;
    int textCode;
    
    #else
    
    #define MAX_DIALOG_COUNT 5
    ZMultiLineEdit * zmeEditList[MAX_DIALOG_COUNT]; 
    QString fileNameList[MAX_DIALOG_COUNT], filePathList[MAX_DIALOG_COUNT];
    int textCodeList[MAX_DIALOG_COUNT];
    
    int curDlg, countDlg; 
    #define edit (zmeEditList[curDlg])
    #define sFileName (fileNameList[curDlg])
    #define sFilePath (filePathList[curDlg])
    #define textCode (textCodeList[curDlg])
    QString dlgCapList[MAX_DIALOG_COUNT];
    #define sDlgCap (dlgCapList[curDlg])
    ZOptionsMenu* DlgMenu;
    void buildDlgMenu();
	#define FIX_DLG_MENU_INDEX 4
    
    QWidgetStack  * wStack;
    
    #endif
    //ZScrollPanel *scrollPanel;
    ZOptionsMenu* MainMenu;
    ZOptionsMenu* FileMenu;
    ZOptionsMenu* EditMenu;
    ZOptionsMenu* CodeMenu;
	QPoint * pos;
	bool isMarck;
	#if defined(EZX_ZN5) || defined(EZX_U9) || defined(EZX_Z6W)
	bool isSelected;
	#endif
	bool fixEditOff;
};



#endif

