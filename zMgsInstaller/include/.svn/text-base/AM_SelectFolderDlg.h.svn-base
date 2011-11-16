// Writet by Ant-ON, <prozanton@gmail.com>
//
// Date: 26.10.10
//
// Lib: libampackage.so
//

#ifndef AM_SELECTFOLDERDLG_H
#define AM_SELECTFOLDERDLG_H

#include "ZSingleSelectDlg.h"

class AM_Folder;
class AM_RegistryObject;

class AM_SelectFolderDlg : public ZSingleSelectDlg
{
	public:
		AM_SelectFolderDlg( const QString &appName, QWidget *parent = 0, const char *name = 0 );
		virtual ~AM_SelectFolderDlg();

		QString getFolder();

	protected:
		bool eventFilter( QObject* o, QEvent* e);

	private:
		QPixmap giveIcon(AM_RegistryObject const*);
		bool initSubFolder (AM_Folder*, ZListBox*);
};

#endif

