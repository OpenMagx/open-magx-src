//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#include "ZFileBrowser.h"
#include <qdir.h>

FileBrowser::FileBrowser ( const QString &filter, QString arg1, QWidget* arg2, unsigned int arg3, ZSkinService::WidgetClsID arg4 )        : ZListBox ( arg1, arg2, arg3, arg4 )
{
  fileName = "";
  nameFilter = filter;
  //setDir ( QDir::currentDirPath() );
  setDir ( "/mmc/mmca1/" );
  connect ( this, SIGNAL ( highlighted ( int ) ), this, SLOT ( itemHighlighted ( int ) ) );
  connect ( this, SIGNAL ( selected ( int ) ), this, SLOT ( itemSelected ( int ) ) );
  connect ( this, SIGNAL ( clicked ( ZSettingItem * ) ), this, SLOT ( itemClicked ( ZSettingItem * ) ) );
}

FileBrowser::~FileBrowser()
{
}

void FileBrowser::setDir ( const QString &path )
{
  RES_ICON_Reader iconReader;
  bool isBack = true;
  QString iconName = "";
  this->clear();
  QDir dir ( path, nameFilter, QDir::Name | QDir::DirsFirst | QDir::IgnoreCase );
  #if defined(EZX_Z6) || defined(EZX_V8)
  dir.setMatchAllDirs ( true );
  #endif
  dir.setFilter ( QDir::Dirs | QDir::Hidden );
  if ( !dir.isReadable() )
    return;
 
  QStringList entries = dir.entryList();
  //entries.sort();
  QStringList::ConstIterator it = entries.begin();
  while ( it != entries.end() )
  {
    if ( *it != "." )
    {
      if (*it != "..") {isBack = isBack && true;} else {isBack = isBack && false;}
      ZSettingItem* Item = new ZSettingItem ( this, QString ( "%I%M" ) );   
      QPixmap pixmap=QPixmap(iconReader.getIcon("fm_folder_small.k", false));      
      Item->setPixmap ( 0, pixmap  );    
      Item->appendSubItem ( 1, *it, false );   
      this->insertItem ( Item,-1,true );       
    }
    ++it;
  }

  dir.setFilter ( QDir::Files | QDir::Hidden );
  entries = dir.entryList();
  //entries.sort();
  it = entries.begin();
  while ( it != entries.end() )
  {
    if ( *it != "." )
    {
      if (*it != "..") {isBack = isBack && true;} else {isBack = isBack && false;}
      ZSettingItem* Item = new ZSettingItem ( this, QString ( "%I%M" ) );
      QPixmap pixmap=QPixmap(iconReader.getIcon("wap_doc_small.k", false));//fm_vid_small.k fm_pic_small.k fm_java_midlet_small.k
      Item->setPixmap ( 0, pixmap);
      Item->appendSubItem ( 1, *it, false );
      this->insertItem ( Item,-1,true );
    }
    ++it;
  }
  
  basePath = dir.canonicalPath();
  if ((isBack) && (basePath != "/") && (basePath.length() > 1)) 
  {
    ZSettingItem* Item = new ZSettingItem ( this, QString ( "%I%M" ) );
	QPixmap pixmap=QPixmap(iconReader.getIcon("gen_back_to_arrw_small.k", false));
    Item->setPixmap ( 0, pixmap  );
    Item->appendSubItem ( 1, QString(".."), false );
    this->insertItem ( Item, 0,true );
    isBack = true;
  }  
}

void FileBrowser::itemHighlighted(int index)
{
  QString a = "";
  ZSettingItem* listitem = (ZSettingItem*)this->item(index);
  a = listitem->getSubItemText(1, 0);
  QString path = basePath + "/" + a;
  if (QFileInfo(path).isFile()) {
    fileName = path;
    emit picked(path);
    emit isFilePicked(TRUE);
  } else {
    fileName = "";
    emit isFilePicked(FALSE);
  }
}

void FileBrowser::itemSelected(int index)
{
  QString a = "";
  ZSettingItem* listitem = (ZSettingItem*)this->item(index);
  a = listitem->getSubItemText(1, 0);
  QString path = basePath + "/" + a;  
  if (QFileInfo(path).isDir())
  {
    this->clear();
    setDir(path);
  }     
  else 
  {
    if (QFileInfo(path).isFile()) 
    {
     fileName = path; 
    }
  }      
}

void FileBrowser::itemClicked(ZSettingItem *item)
{
  QString a = "";
  a = item->getSubItemText(1, 0);
  QString path = basePath + "/" + a;    
  if (QFileInfo(path).isDir())
    setDir(path);
}
