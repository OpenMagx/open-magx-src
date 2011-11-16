//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef ZFILEDLG_H
#define ZFILEDLG_H

#include "GUI_Define.h"
#include "BaseDlg.h"
#include "ZFileBrowser.h"
#include <ZLineEdit.h>
#include <ZMessageDlg.h>

#define Z6KEY_LEFT              0x1012
#define Z6KEY_UP                0x1013
#define Z6KEY_RIGHT             0x1014
#define Z6KEY_DOWN              0x1015
#define Z6KEY_CENTER            0x1004

class ZFileOpenDialog : public MyBaseDlg {
  Q_OBJECT

  public:
    ZFileOpenDialog(); 
    ~ZFileOpenDialog();
    QString getFileName() { return fileName; } 
    QString getFilePath() { return basePath; } 
  private:
    QString fileName;
    QString basePath;      
    FileBrowser* fb;
    
  protected:
    virtual void accept();     
};

class ZFileSaveDialog : public MyBaseDlg {
  Q_OBJECT

  public:
    ZFileSaveDialog(const QString &curPath = "/", const QString &originName = "file.txt"); 
    ~ZFileSaveDialog();
    QString getFileName() { return fileName; } 
    QString getFilePath() { return basePath; }
  private:
    ZLineEdit *zle;
    QString fileName;  
    QString basePath;   
    FileBrowser* fb;
           
  protected:
    virtual void keyPressEvent( QKeyEvent* e);    
    virtual void accept();  

};

#endif
