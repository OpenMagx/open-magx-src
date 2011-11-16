//
// Project: zTextEdit
//
// Description: Text editor for MAGX
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009-2010
//

#ifndef ZFILEBROWSER_H
#define ZFILEBROWSER_H

#include <ZListBox.h>

#if ! (defined(EZX_Z6) || defined(EZX_V8))
#include <ZSettingItem.h>
#include <RES_ICON_Reader.h>
#else
#include <ezxres.h>
#endif

class FileBrowser : public ZListBox
{
  Q_OBJECT
  public:
    FileBrowser(const QString &filter, QString arg1, QWidget* arg2, unsigned int arg3, ZSkinService::WidgetClsID arg4);
    virtual ~FileBrowser();
    
    void setDir(const QString &path);
    QString getFileName() { return fileName; }
    QString getFilePath() { return basePath; }    
    
  signals:
    void picked(const QString &fileName);
    void isFilePicked(bool);
        
  private slots:
    void itemHighlighted(int index);
    void itemSelected(int index);    
    void itemClicked(ZSettingItem *);
        
  private:
    QString nameFilter;
    QString basePath;
    QString fileName;    
};

#endif
