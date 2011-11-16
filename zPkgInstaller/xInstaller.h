#ifndef XINSTALLER
#define XINSTALLER 

#include <qwidget.h>
#include <quuid.h>

#include <AM_MPKGUI.h>
#include <AM_AppLnk.h>

#include <ZProgressDlg.h>

#include <qcopchannel_qws.h>

#define TEMP_PHONE "/ezxlocal/download/mystuff/.tmp/xInstaller"
#define TEMP_MMC "/mmc/mmca1/.tmp/xInstaller"

#define toLog(m) cout << m << endl;

struct AppEntry 
{
	AM_AppLnk::AppType m_type;
	QUuid uid;
	QString bigIcon;
	QString smallIcon;
	QString aniIcon;
	QString simpleIcon;
	QString appId;
	QString directory;
	QString name;
	QString vendor;
	QString nameResourceId;
	bool isLockEnabled;
	bool isShared;
	bool isErasable;
	QString parentFolderUid;
	int position;
	QString exec;
	QString version;
	AM_Global::Device device;
	uint appSize;
};

class xInstaller: public QWidget
{
	Q_OBJECT
	
	public:
		xInstaller();
		~xInstaller();
		
		enum PAK_TYPE
		{
			PAK_UNKNOWN,
			PAK_MGX,
			PAK_PEP,
			PAK_PEP_UPDATE,
		};
		
		bool run( QString sPakgPath );
	
	private:
		void createTmpDir ( QString &tmpDirectory );
		void clearTmpDir ( QString &tmpDirectory, bool onlyIn );
		
		QString getIMEI();
		double getFileSystemFreeSize( AM_Global::Device device );
		QString getPathByDevice( AM_Global::Device );
		
		QString getMgxReadConfig(QString sFile, QString key, QString def);
		void writeToRegistry( AppEntry * app );
		void extAssign( AppEntry * app, QStringList slExt );
		
		QString fixIconName( QString name, QString path );
		QString fixIconToSmall( QString name, QString path );
		QString fixDirectoryName( QString installTo );
		
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
