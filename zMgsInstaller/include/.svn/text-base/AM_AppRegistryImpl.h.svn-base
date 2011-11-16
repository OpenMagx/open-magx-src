
#ifndef AM_APPREGISTRYIMPL_H
#define AM_APPREGISTRYIMPL_H

#include <qstring.h>
#include <qstringlist.h>
#include <quuid.h>
#include <qvaluelist.h>

class AM_AppRegistryEntry 
{
    protected:
        AM_AppRegistryEntry(AM_AppLnk::AppType type = AM_AppLnk::InvalidAppType);
        virtual ~AM_AppRegistryEntry();

    public:
        AM_AppLnk::AppType getApplicationType() const;

    public:
		AM_AppLnk::AppType m_type;
    
        QString uid;
        QString bigIcon;
        QString smallIcon;
        QString aniIcon;
        QString svgIcon;
        QString simpleIcon;
        QUuid appId;
        QString directory;
        QString name;
        QString vendor;
        QString nameResourceId;
        bool isLockEnabled;
        bool isShared;
        bool isErasable;

        QString parentFolderUid;
        int position;

        QStringList otherParentFolderUids;
        QStringList otherPositionIndexList;

        bool isPreloaded;
        AM_Global::Device device;
};

class AM_AppRegistryImpl : public QObject
{
	Q_OBJECT

	uint fix[20];

	public:

		enum AM_AppRegistryFileType {
			SysRegistry = 0,
			SysMenuTree = 1,

			InstalledDB = 2,
			UserMenuTree = 3,
			UserConfig = 4,   
			AppLockRegistry = 5,
			AppRegistryLock = 6,
			AppLockRegistryLock = 7,
			
			CardRegistry = 8,
			MemoryCardConfig = 9,
			MegaSimRegistry = 10,
			MegaSimConfig = 11
		};
		
		static AM_AppRegistryImpl * getInstance();
		void deleteInstance();
		int init();

		int addApplicationEntry(AM_AppRegistryEntry & registryEntry);
		int modifyApplicationEntry(AM_AppRegistryEntry & registryEntry);
		int removeApplicationEntry(AM_AppRegistryEntry & registryEntry);
		int getAppRegistryEntry(const QString & uid, AM_AppRegistryEntry & registryEntry);

	signals:
		void signalFolderOrderUpdated(const QString & folderUid);
		void signalRegistryObjectUpdated(const QString & uid);
		void signalRegistryObjectMoved(const QString &uid, 
				const QString &srcFolderUid, const QString &destFolderUid);
		void signalAppObjectAdded(const QString &uid, const QString &folderUid);
		void signalAppObjectRemoved(const QString &uid, const QString &folderUid);
		void signalCardPlugged(const QStringList & folderUids);
		void signalCardUnplugged(const QStringList & folderUids);
};
    
#endif
