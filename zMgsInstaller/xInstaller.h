#ifndef XINSTALLER
#define XINSTALLER 

#include <qwidget.h>
#include <quuid.h>

#include <AM_MPKGUI.h>
#include <AM_AppLnk.h>

#include <ZProgressDlg.h>

#include <qcopchannel_qws.h>

#define LNG_PATH QString("/ezxlocal/download/mystuff/.system/lng/zPkgInstaller")

#define CHM_PATH "/ezxlocal/download/appwrite/setup/theme"

#define TEMP_PHONE "/ezxlocal/download/mystuff/.tmp/xInstallerSkin"
#define TEMP_MMC "/mmc/mmca1/.tmp/xInstallerSkin"

#define ROOT_PATH_PHONE "/ezxlocal/download/mystuff"
#define ROOT_PATH_MMC "/mmc/mmca1"

#define PATH_PHONE "/ezxlocal/download/mystuff/skin"
#define PATH_MMC "/mmc/mmca1/skin"

#define PATH_7Z "/usr/mbin/7z x %1 -o%2"

#define toLog(m) cout << m << endl;

struct SkinEntry 
{
	QString directory;
	QString name;
	QString vendor;
	QString date;	
	AM_Global::Device device;
	int appSize;
};

class xInstaller: public QWidget
{
	Q_OBJECT
	
	public:
		xInstaller();
		~xInstaller();
		
		bool run( QString sPakgPath );
	
	private:
		void createTmpDir ( QString &tmpDirectory );
		void clearTmpDir ( QString &tmpDirectory, bool onlyIn );
		
		double getFileSystemFreeSize( AM_Global::Device device );
		QString getPathByDevice( AM_Global::Device );
		
		QString getLangLine( QString sFrase );
		
		void fixParamChm(ZConfig *cfg, QString param, QString installPath);
		
		void cancelInstall();		

	public slots:
		void siganalReceived(const QCString&, const QByteArray&);

	private:
		bool bCancel;
		AM_MPKGUI *uiDlg;
		QString sTemp;
		ZProgressDlg *dlgProc;
		QCopChannel * channelStart;
};

#endif
