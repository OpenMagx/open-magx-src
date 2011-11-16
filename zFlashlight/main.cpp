//
// C++ Implementation: zFlashlight
//
// Description:
//
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//
//

#include <ZApplication.h>
#include <ZMessageDlg.h>

#include <qstring.h>
#include <qapplication.h>

#include <iostream>

#include <lm_app_interface.h>

ZApplication* app;

using namespace std;

static int COLOR_OFF = 0x000000;
static int COLOR_ON =  LM_FL_CAMERA_TORCH;


int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	cout << "zFlashlight by Ant-ON" << endl;
	cout << "version: 0.1" << endl;
	
	int fd;
	
	QString ProgDir = QString ( qApp->argv() [0] ) ;
	fd = ProgDir.findRev ( "/" );
	ProgDir.remove( fd+1, ProgDir.length() - fd );
	
	fd = LM_app_connect();
	if ( fd >= 0 )
	{
		short singleMask = LM_REGION_TO_MASK(LM_FL_REGION_CAMERA_FLASH);
		
		if ( LM_app_FLSetcontrol(LM_FL_APP_CTL_FUN_LIGHTS, singleMask) == LM_APP_SUCCESS )
		{
			if ( LM_app_FLUpdate(LM_FL_APP_CTL_FUN_LIGHTS, singleMask, (LM_FL_COLOR_T*)&COLOR_ON) == LM_APP_SUCCESS)
			{
				ZMessageDlg * dlg = new ZMessageDlg("zFlashlight", "zFunlight by Ant-ON\nCopyright (c) 2010", ZMessageDlg::TypeOK, 10*60*100);
				dlg->setTitleIcon( QPixmap( ProgDir+"/zFlashlight_usr.png" ) );
				dlg->exec();
				delete dlg;
				LM_app_FLUpdate(LM_FL_APP_CTL_FUN_LIGHTS, singleMask, (LM_FL_COLOR_T*)&COLOR_OFF);
			}
			LM_app_FLSetcontrol(LM_FL_APP_CTL_FUN_LIGHTS, 0);
		}
        LM_app_disconnect(fd);
	}

	delete app;
	return 1;
}
