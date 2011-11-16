// Copyright 2009-2010, BeZ, Ant-ON

#include "QOverclockApplication.h"
#include "ZConfig.h"
#include "ZDefs.h"

QOverclockApplication::QOverclockApplication(int argc, char **argv) : ZApplication(argc, argv) 
{
	
	if ( QCopChannel::isRegistered( SYSTEM_CHANNEL ) )
	{
		printf( "**** PASS: channel registred\n" );
		pSysChannel = new QCopChannel(SYSTEM_CHANNEL, this);
		connect(pSysChannel, SIGNAL(received(const QCString &,const QByteArray &)),
				this, SLOT(slotSystemMessage(const QCString &,const QByteArray &)));
	} else {
		printf ( "*** FAIL: channel NOT registred\n" ) ;
	}
	#ifndef NO_KEYLOCK
	if ( QCopChannel::isRegistered( PHONE_IDLE_STATUS_TEXT_CHANNEL ) )
	{
		printf( "**** PASS: PHONE_IDLE_STATUS_TEXT_CHANNEL channel registred\n" );
		pSysChannel = new QCopChannel(PHONE_IDLE_STATUS_TEXT_CHANNEL, this);
		connect(pSysChannel, SIGNAL(received(const QCString &,const QByteArray &)),
				this, SLOT(slotSystemMessage(const QCString &,const QByteArray &)));
	} else {
		printf ( "*** FAIL: PHONE_IDLE_STATUS_TEXT_CHANNEL channel NOT registred\n" ) ;
	}
	#endif
	currentMod = 0;

	ZConfig cfg(CPU_CONFIG);
	mod1 = cfg.readNumEntry(QString("Setup"), QString("LCDOn"), 532);
	mod2 = cfg.readNumEntry(QString("Setup"), QString("LCDOff"), 0);
	#ifndef NO_KEYLOCK
	mod3 = cfg.readNumEntry(QString("Setup"), QString("KeyLock"), 133);
	#endif
	#ifdef EZX_E8
	mod4 = cfg.readNumEntry(QString("Setup"), QString("LCDPreOff"), 0);
	#endif	
	cfg.flush();
}

QOverclockApplication::~QOverclockApplication() 
{
}

void QOverclockApplication::slotShutdown()
{
	processEvents();
}

void QOverclockApplication::slotQuickQuit()
{
	processEvents();
}

void QOverclockApplication::slotRaise()
{
	processEvents();
}

void QOverclockApplication::slotUsbStorageInOut (bool)
{
	processEvents();
}


void QOverclockApplication::slotSystemMessage(const QCString &msg, const QByteArray &data)
{
	printf("received system message: %s\n", msg.data() );
	
	if ( msg == LCD_ON )
	{
		updateCPU(1);
	} else
	if ( msg == LCD_OFF )
	{
		updateCPU(2);
	} 
	#ifndef NO_KEYLOCK
	else	
	if ( msg == KEY_LOCK )	
	{
		if ( UTIL_GetKeypadLockStatus() )
		{
			updateCPU(3);
		}
	}
	#endif
	#ifdef EZX_E8
	else	
	if ( msg == LCD_PRE_OFF )	
	{
		updateCPU(4);
	}
	#endif
}

void QOverclockApplication::updateCPU(int n)
{
	if ( currentMod == n)
		return;
	switch (n)
	{
		case 1:
		{
			modToCPU(mod1);
			break;
		}
		case 2:
		{
			modToCPU(mod2);
			break;
		}	
		#ifndef NO_KEYLOCK
		case 3:
		{
			modToCPU(mod3);
			break;
		}			
		#endif
		#ifdef EZX_E8
		case 4:
		{
			modToCPU(mod4);
			break;
		}
		#endif		
	}
	currentMod = n;
}

void QOverclockApplication::modToCPU(int mod)
{
	if ( mod < 1)
	{
		printf("CPU clocks: set to default (auto) \n");
		system("pmtool -d 1");		
	} else
	{
		printf(QString("CPU clocks: ")+QString::number(mod)+QString(" MHz \n"));
		system("pmtool -d 0");
		system(QString("echo ")+QString::number(mod).data()+QString(" > /sys/mpm/op"));		
	}
}
