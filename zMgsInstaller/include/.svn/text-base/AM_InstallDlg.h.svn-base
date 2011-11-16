// Writet by Ant-ON, <prozanton@gmail.com>
//
// Date: 26.10.10
//
// Lib: libampackage.so
//

#ifndef AM_INSTALLDLG_H
#define AM_INSTALLDLG_H

#include "AM_Global.h"
#include "ZPopup.h"

class AM_InstallDlg : public ZPopup
{
    Q_OBJECT
    
    uint fix[20];
    
public:
    enum Type { Qt = 1, Java = 2 };

    AM_InstallDlg( Type type, const QString &appName, int size, QWidget *parent = 0, const char *name = 0 );
    virtual ~AM_InstallDlg();

    static bool deviceMounted( AM_Global::Device device );

    QString getGroup() const;
    AM_Global::Device getDevice( void ) const;

protected:
    virtual void init( Type type );

private slots:
    void slotCancel();
    void slotOk();
};

#endif
