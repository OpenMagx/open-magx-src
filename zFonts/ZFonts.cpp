//
// C++ Implementation: ZFonts
//
// Description:
//
//
// Author: BeZ <bezols@gmail.com>, (C) 2008
// Author: Ant-ON <prozanton@gmail.com>, (C) 2009
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include "ZFonts.h"
#include "BaseDlg.h"
#include "ZAboutDlg.h"

#include <qpixmap.h>
#include <qfontmanager_qws.h>
#include <qfileinfo.h>
#include <qfontdatabase.h>
#include <qdir.h>
#include <qcopchannel_qws.h>

#include <ZApplication.h>
#include <ZListBox.h>
#include <ZSoftKey.h>
#include <ZOptionsMenu.h>
#include <ZSingleCaptureDlg.h>
#include <ZSingleSelectDlg.h>
#include <ZMessageDlg.h>

#define LNG_PATH QString("/ezxlocal/download/mystuff/.system/lng/zFonts")
//#define LNG_PATH ProgDir

ZFonts::ZFonts ( QWidget* parent, const char* name, WFlags fl )
    : ZKbMainWidget ( ZHeader::MAINDISPLAY_HEADER, NULL, "ZMainWidget", 0 )
{
	ProgDir = QString ( qApp->argv() [0] ) ;
	int i = ProgDir.findRev ( "/" );
	ProgDir.remove ( i+1, ProgDir.length() - i );	

	sViewText="";

	CreateWindow ( parent );
	show();
}

ZFonts::~ZFonts()
{

}

void ZFonts::CreateWindow ( QWidget* parent )
{
	//Set title window
	setMainWidgetTitle ( "zFonts" );
	
	lbFonts = new ZListBox(this);
	
	QFont font ( qApp->font() ); 
	font.setPointSize ( 18 );
	lbFonts->setItemFont( ZListBox::LISTITEM_REGION_A, ZListBox::StStandard, font );	
	lbFonts->setItemFont( ZListBox::LISTITEM_REGION_A, ZListBox::StHighlighted, font );	
	
	connect ( lbFonts, SIGNAL( selected(int) ), this, SLOT( slot_fontSelect(int) ) );
	
	setContentWidget( lbFonts );

	fillFonts();

	//Create SoftKey and Menu
	ZSoftKey *softKey = new ZSoftKey ( NULL , this , this );
	
	QRect rect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	ZOptionsMenu* menu = new ZOptionsMenu ( rect, softKey, NULL, 0 );
	menu->setItemSpacing(12);
	
	QPixmap * pm = new QPixmap();

	pm->load(ProgDir+ "/view_font.png");
	menu->insertItem ( tr("TXT_RID_OPTION_PREVIEW", "Preview"), NULL, pm, true, 0, 0 );
	pm->load(ProgDir+ "/set_fonts.png");
	menu->insertItem ( tr("TXT_RID_SOFTKEY_INSTALL", "Install"), NULL, pm, true, 1, 1 );
	pm->load(ProgDir+ "/about.png");
	menu->insertSeparator(2, 2); 
	menu->insertItem ( tr("TXT_RID_SOFTKEY_ABOUT_JAVA", "About").replace("Java",""), NULL, pm, true, 3, 3 );
	pm->load(ProgDir+ "/exit.png");
	menu->insertItem ( tr("TXT_RID_OPTION_EXIT", "Exit"), NULL, pm, true, 4, 4 );
	
	menu->connectItem ( 0, this, SLOT ( slot_preview() ) );
	menu->connectItem ( 1, this, SLOT ( slot_install() ) );
	menu->connectItem ( 3, this, SLOT ( slot_about() ) );
	menu->connectItem ( 4, qApp, SLOT ( quit() ) );	
	
	softKey->setText ( ZSoftKey::LEFT, tr("TXT_RID_SOFTKEY_OPTIONS", "Options"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setText ( ZSoftKey::RIGHT, tr("TXT_RID_OPTION_EXIT", "Exit"), ( ZSoftKey::TEXT_PRIORITY ) 0 );
	softKey->setOptMenu ( ZSoftKey::LEFT, menu );
	softKey->setClickedSlot ( ZSoftKey::RIGHT, qApp, SLOT ( quit() ) );
	
	setSoftKey ( softKey );
}

QString ZFonts::getProgramDir()
{
	return ProgDir;
}

void ZFonts::slot_about()
{
	ZAboutDialog* aboutDlg = new ZAboutDialog();
	aboutDlg->exec();
	delete aboutDlg;
}

#define getFontPath(a) (*((QString*)((a)->getReservedData())))

QString ZFonts::getViewText()
{
	
	if ( sViewText.length() == 0 )
	{
		QString curLng;
		ZConfig cfg( "/ezxlocal/download/appwrite/setup/ezx_system.cfg" );
		curLng = cfg.readEntry("SYS_SYSTEM_SET", "LanguageType", "");
		if ( curLng.length() > 1 )
			curLng = QString(curLng[0]) + QString(curLng[1]);
			
		ZConfig cfg2( LNG_PATH+"/zFonts.lng" );
		sViewText = QString::fromUtf8(cfg2.readEntry("ViewString", curLng, "").utf8()).replace("/n","\n");
		if ( sViewText.length() == 0 )
			sViewText = QString::fromUtf8(cfg2.readEntry("ViewString", "en", "").utf8()).replace("/n","\n");			
	}

	return sViewText;
}

void ZFonts::slot_preview()
{
	int n = lbFonts->currentItem();
	
	if ( n<0 )
		if ( lbFonts->count()>0 )
			n=0;
		else
			return;
			
	slot_fontSelect(n);
}

void ZFonts::slot_install()
{
	int n = lbFonts->currentItem();
	
	if ( n<0 )
		if ( lbFonts->count()>0 )
			n=0;
		else
			return;
	
	QString sFontPath = getFontPath(lbFonts->item(n));
	QString sFontName = QFileInfo(sFontPath).baseName();		
	
	ZSingleSelectDlg * ssdInstallAs = new ZSingleSelectDlg( sFontName, tr("FMT_RID_INSTRUCTIONALTXT_INSTALLING_1","Install to").arg("") );
	QStringList list;
	list.append( tr("TXT_RID_OPTION_TEXT", "Text") );
	list.append( tr("TXT_RID_STANDARD_JAVAPIM_CONTACT_PHONENUMBER", "Phone Number") );		
	ssdInstallAs->addItemsList( list );
	
	if ( ssdInstallAs->exec() == QDialog::Accepted )
	{
		ZMessageDlg * dlg = new ZMessageDlg("zFonts", 
				QObject::tr("TXT_RID_INSTRUCTIONALTXT_PLEASE_WAIT","Update..."),		
				ZMessageDlg::TypeCustom, 0, this);
		dlg->setTitleIcon( "info_pop.g" );
		dlg->show();
		qApp->processEvents();
		
		QString sInstallTo;
		if ( ssdInstallAs->getCheckedItemIndex()==0 )
			sInstallTo = "/ezxlocal/fonts/AMCSL.TTF";
		else
			sInstallTo = "/ezxlocal/fonts/NUMBER.TTF";

		system(QString("cp -a %1 %2").arg(sFontPath).arg(sInstallTo) );
        
		system("mot_reboot");        
	}
}

void ZFonts::slot_fontSelect(int n)
{
	previewFont(getFontPath(lbFonts->item(n)));
}

void ZFonts::previewFont(QString sFontPath)
{
	QString sFontName = QFileInfo(sFontPath).baseName();

    QFontFactory* ffFactory = qt_fontmanager->factories.at(0);
    QDiskFont* dfFont = new QDiskFont(ffFactory, sFontName, false, 20, 0, "s", sFontPath);
    qt_fontmanager->diskfonts.append(dfFont);
    QFontDatabase::qwsAddDiskFont(dfFont);
    
	QFont fOrg = QFont::defaultFont();
	QFont fNew = fOrg;
	fNew.setFamily( sFontName );
	QFont::setDefaultFont( fNew );  

	ZSingleCaptureDlg* scdPreview = new ZSingleCaptureDlg(sFontName,"", ZSingleCaptureDlg::TypeTextField, this);
	scdPreview->enableAia(false);
	QPixmap pm( ProgDir+"/fonts.png" );
	scdPreview->setTitleIcon(pm);  
	                                               
	ZSoftKey* skKey = scdPreview->getSoftKey();
	skKey->disableClickedSlot(ZSoftKey::LEFT);
	skKey->setText(ZSoftKey::RIGHT, tr("TXT_RID_SOFTKEY_BACK","Back"), (ZSoftKey::TEXT_PRIORITY)0);
	skKey->setText(ZSoftKey::LEFT, "", (ZSoftKey::TEXT_PRIORITY)0);

	ZMultiLineEdit* mleText = scdPreview->getMultiLineEdit();
	mleText->setText(getViewText());
	mleText->setUnderline( false );
	mleText->setFocus();

	scdPreview->exec();
	delete scdPreview;
	
	QFont::setDefaultFont( fOrg );  	
}

void ZFonts::fillFonts()
{
	lbFonts->clear();
	fillFontsByDir("/usr/language/fonts");	
	fillFontsByDir("/mmc/mmca1/fonts");
	fillFontsByDir("/mmc/mmca1/.fonts");	
	fillFontsByDir("/ezxlocal/download/mystuff/fonts");
	fillFontsByDir("/ezxlocal/download/mystuff/.fonts");	
}

void ZFonts::fillFontsByDir(QString sDir)
{
	QStringList slFonts;
	slFonts.clear();
	QDir dir( sDir );
	dir.setFilter( QDir::Files );
	dir.setNameFilter("*.ttf;*.TTF");
	slFonts = dir.entryList();
	
	QString * path;
	QPixmap pm( ProgDir + "/fonts.png");
	for ( QStringList::Iterator it = slFonts.begin(); it != slFonts.end(); ++it ) 
	{
		ZSettingItem* item = new ZSettingItem(lbFonts, "%I%M");
		item->setPixmap( 0, pm  );
		item->appendSubItem( 1, QString::fromUtf8(*it) );
		path = new QString(sDir+"/"+(*it));
		item->setReservedData( (int)path );
		lbFonts->insertItem( item );      
	}
}

