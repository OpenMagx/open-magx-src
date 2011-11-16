// Copyright 2009-2010, BeZ, Ant-ON

#ifndef OVERCLOCK_APPLICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <ZApplication.h>
#include <qcopchannel_qws.h>

class QOverclockApplication : public ZApplication 
{
    Q_OBJECT
  public:
    QOverclockApplication(int argc, char **argv);
    virtual ~QOverclockApplication();

	public:
	  bool isLCDOn;
	  bool isSliderOpened;
	  bool isLock;
	  int currentMod;
	  int mod1, mod2, mod3;
	  #ifdef EZX_E8
	  int mod4;
	  #endif
		
	private:
		QCopChannel* pSysChannel; 
	
	protected slots:
		virtual void slotShutdown();	
		virtual void slotQuickQuit();
		virtual void slotRaise();
		virtual void slotUsbStorageInOut (bool storagIn);
		void updateCPU(int n);
		void modToCPU(int mod);
		void slotSystemMessage(const QCString &msg, const QByteArray &data);
				
		
};

#endif
