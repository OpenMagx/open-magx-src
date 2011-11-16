//
// C++ Implementation: zsnap
//
// Description:
//
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2011
//
//
#include <ZApplication.h>

#include <qstring.h>
#include <qapplication.h>

#include <iostream>

ZApplication* app;

using namespace std;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	cout << "zsnap by Ant-ON" << endl;
	
	if ( argc>=3 )
	{
		int w=atoi(argv[1]);
		int h=atoi(argv[2]);
		
		QWidget * wMain = new QWidget( 0 );
		wMain->setFocusPolicy( QWidget::NoFocus );
		wMain->setFixedSize(w, h);
		wMain->setBackgroundMode( QWidget::NoBackground );
		wMain->show();

		QPixmap pm(w, h);
		bitBlt( &pm, 0, 0, wMain, 0, 0, w, h, Qt::CopyROP, true);
		pm.save(argv[3],"PNG");
	}
	delete app;
	return 1;
}
