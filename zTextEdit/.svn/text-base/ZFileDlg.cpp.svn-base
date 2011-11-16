//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#include "ZFileDlg.h"
#include "ZFileBrowser.h"
#include <qpixmap.h>
#include <qlabel.h>
#include <ZApplication.h>
#include <ZSoftKey.h>
#include <ZLabel.h>

#include "lng.h"
extern ZLng* lng;

//************************************************************************************************
//************************************** class ZFileOpenDialog ***********************************
//************************************************************************************************
ZFileOpenDialog::ZFileOpenDialog()
  :MyBaseDlg()
{
  setMainWidgetTitle ( lng->getString("OPEN") );
  
  QWidget *myWidget = new QWidget ( this ); 
  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  fb = new FileBrowser("*", QString ( "%I%M" ), myWidget, 0, ( ZSkinService::WidgetClsID ) 4);
  fb->setDir("/mmc/mmca1/"); 
  QObject::connect(fb, SIGNAL(isFilePicked(bool)), SLOT(filePicked(bool)));
   
  myVBoxLayout->addWidget ( fb, 1 );
  
  setContentWidget ( myWidget );
  
  ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
  softKey->setText ( ZSoftKey::LEFT, lng->getString("OK"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, lng->getString("CANCEL"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( reject() ) );
  softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
  setCSTWidget ( softKey ); 
}

ZFileOpenDialog::~ZFileOpenDialog()
{

}

void ZFileOpenDialog::accept()
{
  fileName = fb->getFileName();
  basePath = fb->getFilePath();
  MyBaseDlg::accept();
}

//************************************************************************************************
//************************************** class ZFileSaveDialog ***********************************
//************************************************************************************************
ZFileSaveDialog::ZFileSaveDialog(const QString &curPath, const QString &originName)
  :MyBaseDlg()
{
  setMainWidgetTitle ( lng->getString("SAVE") );
	
  QWidget *myWidget = new QWidget ( this );
  QVBoxLayout *myVBoxLayout = new QVBoxLayout ( myWidget, 0 );
  
  zle = new ZLineEdit(originName, myWidget, "ZLineEdit");
  zle->setTitle( lng->getString("ENTER_FILE_NAME") );
  
  myVBoxLayout->addWidget ( zle, 0 );

  fb = new FileBrowser("*", QString ( "%I%M" ), myWidget, 0, ( ZSkinService::WidgetClsID ) 4);
  fb->setDir(curPath);
  QObject::connect(fb, SIGNAL(isFilePicked(bool)), SLOT(filePicked(bool)));
  myVBoxLayout->addWidget ( fb, 1 );
  
  setContentWidget ( myWidget );  
  
  #if defined(EZX_E8) || defined(EZX_EM30)
  //For activ all button on E8/EM30
  setMorphMode(3);
  #endif
  
  ZSoftKey *softKey = new ZSoftKey ( NULL, this, this );
  softKey->setText ( ZSoftKey::LEFT, lng->getString("OK"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setText ( ZSoftKey::RIGHT, lng->getString("CANCEL"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
  softKey->setClickedSlot ( ZSoftKey::RIGHT, this, SLOT ( reject() ) );
  softKey->setClickedSlot ( ZSoftKey::LEFT, this, SLOT ( accept() ) );
  setCSTWidget ( softKey );
}

ZFileSaveDialog::~ZFileSaveDialog()
{

}

void ZFileSaveDialog::keyPressEvent ( QKeyEvent* e )
{
  switch ( e->key() ) 
  {
    case Z6KEY_LEFT:
    case Z6KEY_RIGHT: 
    {
      zle->setFocus();
      break;
    }
    default:
      MyBaseDlg::keyPressEvent ( e );
  }   

}

void ZFileSaveDialog::accept()
{
  // check multilineedit
  QString txt = zle->text();
  if (txt.length()>0)
  {
    fileName = txt;
    basePath = fb->getFilePath();
    MyBaseDlg::accept();
  }
  else
  {
    ZMessageDlg *dlg = new ZMessageDlg ( lng->getString("ERROR"), "Please enter a file name.", ZMessageDlg::TypeOK, 0, this, "About", true, 0 );
    dlg->setIcon(QPixmap("Dialog_Question_Mark.gif"));
    dlg->exec();
    delete dlg;
    dlg = NULL;  
  }
}
