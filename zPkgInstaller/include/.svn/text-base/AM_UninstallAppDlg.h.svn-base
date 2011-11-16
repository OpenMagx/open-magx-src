// Writet by Ant-ON, <prozanton@gmail.com>
//
// Date: 26.10.10
//
// Lib: libampackage.so
//

#ifndef AM_UNINSTALLAPPDLG_H
#define AM_UNINSTALLAPPDLG_H

#include <ZPopup.h>

class AppListBoxItem;

class AM_UninstallAppDlg : public ZPopup
{
    Q_OBJECT
    
    uint fix[10];
public:
    AM_UninstallAppDlg( QWidget *parent = 0, const char *name = 0 );
    ~AM_UninstallAppDlg();

    void insertApp( int n, const QString &name, const QString &iconName, bool bRunning = false );
    void getSelectedAppIds( QArray<int>& );
    bool init();

protected:
    bool itemSelected(void);

protected slots:
    void slotClicked( AppListBoxItem *item );
    void slotCancelDelete( void );
    void slotAboutToShowLeftMenu( void );
    void slotCancelOption (void);
    void slotSelectAll( void );
    void slotUnselectAll(void);
};

#endif
