//
// C++ Implementation: zPkgInstaller
//
// Description:
//
//
// Author: Ant-ON <prozanton@gmail.com>, (C) 2010
//
//
#include <ZApplication.h>
#include <qstring.h>
#include <iostream>

#include "xInstaller.h"
ZApplication* app;

using namespace std;

int main ( int argc, char **argv )
{
	app = new ZApplication ( argc, argv );
	cout << "zPkgInstaller by Ant-ON" << endl;

	if ( argc > 1 )
	{
		xInstaller * pakg = new xInstaller();
		
		QString sFile;
		if (argc > 2) 
			sFile = argv[2];
		else
			sFile = argv[1];
			
		cout << "Process packege: " << sFile << endl;
		pakg->run( sFile );
	}

	cout << "Exit app" << endl;
	delete app;
	app = NULL;
	return 1;
}
