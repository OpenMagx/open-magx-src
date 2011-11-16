// Writet by Ant-ON, <prozanton@gmail.com>
//
// Date: 26.10.10
//
// Lib: libampackage.so
//

#ifndef AM_MPKGUI_H
#define AM_MPKGUI_H

#include "AM_Global.h"
#include "ZPopup.h"


class AM_MPKGUI: public QWidget//ZPopup
{
    Q_OBJECT
    	
    uint fix[40];
    	
	public:
		AM_MPKGUI();
		~AM_MPKGUI();
		
		enum INSTALL_TYPE
		{
			ENUM_1,
			ENUM_2,
			ENUM_3
		};

		
		//Process
		void initProgressBar(QString const&, QString const& caption, QString const& description, int max=100, bool canHide = false);
		void setProgressBar(int p, bool = false);
		
		void disableProgressCancel();
		
		//Info message
		static bool appDetailsCardDlg(QString const&, QString const& appName, QString const& autor, QString const& ver, QString const& size);
		static void appExistsDlg();
		
		//Install
		static void installFolderDlg(QString const& parenUUID /*??*/, QString& installToMenuUID); // ??? install folder in menu. 
		static void installLocationDlg(QString const& appName, int, AM_Global::Device& installToDevice);
		static void applicationInstalledDlg(QString const&, AM_MPKGUI::INSTALL_TYPE const&);
		static void appInstalledNoLaunchDlg(QString const& appName);			
		static void installationFailedDlg();
			
		//Uninstal
		static void deleteDlg(QString const&, QPixmap const&);
		
		//Update
		static bool updateDlg(QString const& name, QString const& oldVersion, QString const& newVersion);
		static void updateFailedDlg();
		
		//Move
		static void movePkgDlg(AM_Global::Device);
		static void moveCompleteDlg();
		static void moveFailedDlg();		
		
		//Question
		static void userConfirmCancelDlg(QString const& appName);
		
		//Error
		static void corruptFileDlg();
		static void certificateFailureDlg();
		static void invalidPkgDlg();
		static void errorUninstallDlg();
		static void missingFileDlg();
		
		static void memFullDlg(AM_Global::Device, unsigned int needSize);
		
		static void requestOngoingErrorDlg();
		
		//Utils
		bool isCardMounted();
	
		
		//Othe
		void appRunningDlg_i();
		void appRunningDlg_m();
		void appRunningDlg_u();
		void deleteTransDlg();
		void noCertificateDlg(QString const&);
		void reinsertMMCDlg();
		
	public slots:
		void slotCancelClicked();		
};

#endif
