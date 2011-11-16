//
// Writen by Ant-ON, 2010
//
// email: prozanton@gmail.com
//

#ifndef PUBLIC_UTIL_SYS_H 
#define PUBLIC_UTIL_SYS_H

#include <qwidget.h>

//For change SDK for ZN5/U9/Z6W
//#include "ZMyConfig.h"


typedef enum
{
	NONE=0
} AUDIO_PATH;

#ifdef __cplusplus
extern "C"
{
#endif
	// Returned:
	//
	// 1 - On/Activ/Enable
	// 0 - Off/Disable

	int UTIL_GetActiveAccount();
	int UTIL_GetActivePin();
	int UTIL_GetAddrLaunchCamera();
	int UTIL_GetAlarmServerStatus();
	int UTIL_GetAMApplicationStatus();
	int UTIL_GetAMSsMsg();
	int UTIL_GetApplicationManagerTableAddress();
	int UTIL_GetAppLockSessionStatus();
	int UTIL_GetBatteryLevel();
	int UTIL_GetBatteryPercent();
	int UTIL_GetBatteryStatus();
	int UTIL_GetBlendingColor();
	int UTIL_GetBlendingCST();
	int UTIL_GetBlendingGNB();
	int UTIL_GetBlendingPercentage();
	int UTIL_GetBlendingScrollBar();
	int UTIL_GetBlendingStatusBar();
	int UTIL_GetBtA2dpStatus();
	int UTIL_GetBtConnCount();
	int UTIL_GetBtFunLightStatus();
	int UTIL_GetBtHandfreeStatus();
	int UTIL_GetBTHSStatus();
	int UTIL_GetBtScoReadyForVr();
	int UTIL_GetBtStatus();
	bool UTIL_GetCallBarringStatus();
	int UTIL_GetCallChargeType();
	int UTIL_GetCallConnectedStatus();
	int UTIL_GetCallDlgPopup();
	int UTIL_GetCallForwardStatus();
	#ifdef EZX_ZN5
	int UTIL_GetCameraStatus();
	#endif
	int UTIL_GetCardType();
	int UTIL_GetCarrierKeySettings();
	bool UTIL_GetChargeCompletedStatus();
	int UTIL_GetChargeStatus();
	int UTIL_GetCountryId();
	int UTIL_GetCPHSCallForwardStatus();
	int UTIL_GetCphsCspStatus();
	int UTIL_GetCphsInfoNumsStatus();
	int UTIL_GetCphsLineLockStatus();
	int UTIL_GetCphsOperatorName();
	int UTIL_GetCphsOpnShortformSatus();
	int UTIL_GetCphsSimCardStatus();
	int UTIL_GetCphsVMStatus();
	int UTIL_GetCSDCallStatus();
	AUDIO_PATH UTIL_GetCurrentSystemAudioPath();
	int UTIL_GetDataCallStaus();
	int UTIL_GetDataConnStatus();
	int UTIL_GetDateFormat();
	int UTIL_GetDialHyphenation();
	int UTIL_GetDisplayTimer();
	int UTIL_GetDlgPriority();
	int UTIL_GetEarpieceSafety();
	int UTIL_GetEFEMMode();
	int UTIL_GetEgprsServiceStatus();
	int UTIL_GetEgprsTransStatus();
	int UTIL_GetEMUBus_Acc_Status();
	int UTIL_GetEMUDeviceType();
	int UTIL_GetEnteringSubsidyCode();
	int UTIL_GetFlipStatus();
	int UTIL_GetGprsActivatedStatus();
	int UTIL_GetGprsAttachStatus();
	int UTIL_GetGprsFeatureStatus();
	int UTIL_GetGprsServiceStatus();
	int UTIL_GetHeadsetStatus();
	int UTIL_GetHideState();
	int UTIL_GetHKSoundInfo();
	int UTIL_GetHomeZoneName();
	int UTIL_GetHomeZoneStatus();
	int UTIL_GetIdleFocus();
	int UTIL_GetIncomingCallStatus();
	int UTIL_GetInComposer();
	int UTIL_GetIrdaBusyStatus();
	#ifdef EZX_ZN5
	int UTIL_GetIsOrientationLandscape();
	#endif
	bool UTIL_GetKeypadLockStatus();
	int UTIL_GetLanguageCode();
	int UTIL_GetLanOpenLayout();
	#ifdef EZX_ZN5
	int UTIL_GetLensCoverStatus();
	#endif
	bool UTIL_GetLowBatteryStatus();
	void UTIL_Get_Lum(int&);
	int UTIL_GetMAType();
	int UTIL_GetMMCSDInfo();
	int UTIL_GetMMCSDStatus();
	int UTIL_GetMMSLaunchCamera();
	void UTIL_GetNetworkId(char n[16]);
	int UTIL_GetNetworkStatus();
	int UTIL_GetNotiPopupStatus();
	bool UTIL_GetOpeatorLogoStatus();
	void UTIL_GetOrgSpnName(char s[61]);
	int UTIL_GetPhoneApplicationStatus();
	int UTIL_GetPhoneAudioDeviceStatus();
	AUDIO_PATH UTIL_GetPhoneAudioPath();
	int UTIL_GetPhoneAutoLockTime();
	int UTIL_GetPhoneCallIconIndex();
	bool UTIL_GetPhoneInCall();
	int UTIL_GetPhoneLine();
	int UTIL_GetPhoneLockStatus();
	int UTIL_GetPhoneSystemStatus();
	int UTIL_GetPinStatus();
	int UTIL_GetPowerOffStatus();
	int UTIL_GetPowerOnCliUIStatus();
	int UTIL_GetPowerOnHandleStatus();
	int UTIL_GetPowerOnMode();
	int UTIL_GetPowerOnModuleRunningStatus();
	int UTIL_GetPowerOnProcess();
	int UTIL_GetPowerOnTableAddress();
	int UTIL_GetRestrictId();
	int UTIL_GetRestrictNextId();
	int UTIL_GetRFMode();
	int UTIL_GetRoamStatus();
	int UTIL_GetScreensaverStatus();
	int UTIL_GetScreensaverTimer();
	int UTIL_GetSecurityKeyLockState();
	void UTIL_GetServiceName(char s[61]);
	int UTIL_GetSideKeyLock();
	int UTIL_GetSignalQuality();
	int UTIL_GetSimCardChangedStatus();
	int UTIL_GetSimCardStatus();
	int UTIL_GetSimLock();
	int UTIL_GetSIMPinBatteryStatus();
	int UTIL_GetSIMPlayTone();
	int UTIL_GetSliderStatus();
	int UTIL_GetSpeakerPhoneSetting();
	bool UTIL_GetSpnDisplayedStatus();
	int UTIL_GetSpnName(char s[61]);
	int UTIL_GetSTKSetupMenuStatus();
	int UTIL_GetSubsidyStatus();
	int UTIL_GetTalkingPhoneStatus();
	int UTIL_GetThemeInfo();
	int UTIL_GetTimeFormat();
	int UTIL_GetTimingPhoneLock();
	int UTIL_GetTotalDataBytes();
	int UTIL_GetTotalDuration();
	int UTIL_GetTPSoundInfo();
	int UTIL_GetTransparency();
	int UTIL_GetTTYDeviceStatus();
	int UTIL_GetTZEnv();
	int UTIL_GetUNSwitchStatus();
	int UTIL_GetUSBChargingStatus();
	int UTIL_GetUSBConnectionStatus();
	int UTIL_GetUSBDeviceType();
	int UTIL_GetUsbMassStorage();
	int UTIL_GetVerifyPin1Status();
	int UTIL_GetVRSupporting();
	int UTIL_GetWidgetSkinnableProp();
	int UTIL_GetWifiCampStatus();
	int UTIL_GetWifiConnectionInProgress();
	int UTIL_GetWifiLingertime();
	#ifdef EZX_ZN5
	int UTIL_GetWifiLinkStatus();
	#endif
	void UTIL_GetWifiProfileName(char n[129]);
	int UTIL_GetWifiSignalBar();
	int UTIL_GetWifiUMALingertime();
	
	#ifdef EZX_Z6W
	int UTIL_GetCLIIdleStatus();
	#endif	

	void UTIL_SetActiveAccount(int);
	void UTIL_SetActivePin(int);
	void UTIL_SetAddrLaunchCamera(int);
	void UTIL_SetAlarmServerStatus(int);
	void UTIL_SetAMApplicationStatus(int);
	void UTIL_SetAMSsMsg(int);
	void UTIL_SetAppLockSessionStatus(int);
	void UTIL_SetBatteryLevel(int);
	void UTIL_SetBatteryPercent(int);
	void UTIL_SetBatteryStatus(int);
	void UTIL_SetBlendingColor(int);
	void UTIL_SetBlendingCST(int);
	void UTIL_SetBlendingGNB(int);
	void UTIL_SetBlendingPercentage(int);
	void UTIL_SetBlendingScrollBar(int);
	void UTIL_SetBlendingStatusBar(int);
	void UTIL_SetBtA2dpStatus(int);
	void UTIL_SetBtConnCount(int);
	void UTIL_SetBtFunLightStatus(int);
	void UTIL_SetBtHandfreeStatus(int);
	void UTIL_SetBTHSStatus(int);
	void UTIL_SetBtScoReadyForVr(int);
	void UTIL_SetBtStatus(int);
	void UTIL_SetCallBarringStatus(bool);
	void UTIL_SetCallChargeType(int);
	void UTIL_SetCallConnectedStatus(int);
	void UTIL_SetCallDlgPopup(int);
	void UTIL_SetCallForwardStatus(int);
	#ifdef EZX_ZN5
	void UTIL_SetCameraStatus(int);
	#endif
	void UTIL_SetCardType(int);
	void UTIL_SetChargeCompletedStatus(bool);
	void UTIL_SetChargeStatus(int);
	void UTIL_SetCountryId(int);
	void UTIL_SetCPHSCallForwardStatus(int);
	void UTIL_SetCphsInfo(int);
	void UTIL_SetCphsLineLockStatus(int);
	void UTIL_SetCphsOperatorName(int);
	void UTIL_SetCSDCallStatus(int);
	void UTIL_SetCurrentSystemAudioPath(AUDIO_PATH);
	void UTIL_SetDataCallStatus(int);
	void UTIL_SetDataConnStatus(int);
	void UTIL_SetDateFormat(int);
	void UTIL_SetDialHyphenation(int);
	void UTIL_SetDisplayTimer(int);
	void UTIL_SetDlgPriority(int);
	void UTIL_SetEarpieceSafety(int);
	void UTIL_SetEFEMMode(int);
	void UTIL_SetEgprsServiceStatus(int);
	void UTIL_SetEgprsTransStatus(int);
	void UTIL_SetEMUBus_Acc_Status(int);
	void UTIL_SetEMUDeviceType(int);
	void UTIL_SetEnteringSubsidyCode(int);
	void UTIL_SetFlipStatus(int);
	void UTIL_SetGprsActivatedStatus(int);
	void UTIL_SetGprsAttachStatus(int);
	void UTIL_SetGprsFeatureStatus(int);
	void UTIL_SetGprsServiceStatus(int);
	void UTIL_SetHeadsetStatus(int);
	void UTIL_SetHideState(int);
	void UTIL_SetHKSoundInfo(int);
	void UTIL_SetHomeZoneName(int);
	void UTIL_SetHomeZoneStatus(int);
	void UTIL_SetIdleFocus(int);
	void UTIL_SetIncomingCallStatus(int);
	void UTIL_SetInComposer(int);
	void UTIL_SetIrdaBusyStatus(int);
	#ifdef EZX_ZN5
	void UTIL_SetIsOrientationLandscape(int);
	#endif
	void UTIL_SetKeypadLockStatus(bool);
	void UTIL_SetLanguageCode(int);
	void UTIL_SetLanOpenLayout(int);
	#ifdef EZX_ZN5
	void UTIL_SetLensCoverStatus(int);
	#endif
	void UTIL_SetLowBatteryStatus(bool);
	void UTIL_SetMAType(int);
	void UTIL_SetMMCSDInfo(int);
	void UTIL_SetMMCSDStatus(int);
	void UTIL_SetMMSLaunchCamera(int);
	void UTIL_SetNetworkId(char n[16]);
	void UTIL_SetNetworkStatus(int);
	void UTIL_SetNotiPopupStatus(int);
	void UTIL_SetOpeatorLogoStatus(bool);
	void UTIL_SetOrgSpnName(char s[61]);
	void UTIL_SetPhoneApplicationStatus(int);
	void UTIL_SetPhoneAudioDeviceStatus(int);
	void UTIL_SetPhoneAudioPath(AUDIO_PATH);
	void UTIL_SetPhoneAutoLockTime(int);
	void UTIL_SetPhoneCallIconIndex(int);
	void UTIL_SetPhoneInCall(bool);
	void UTIL_SetPhoneLine(int);
	void UTIL_SetPhoneLockStatus(int);
	void UTIL_SetPinStatus(int);
	void UTIL_SetPowerOffStatus(int);
	void UTIL_SetPowerOnCliUIStatus(int);
	void UTIL_SetPowerOnHandleStatus(int);
	void UTIL_SetPowerOnMode(int);
	void UTIL_SetPowerOnModuleRunningStatus(int);
	void UTIL_SetPowerOnProcess(int);
	void UTIL_SetRestrictId(int);
	void UTIL_SetRestrictNextId(int);
	void UTIL_SetRFMode(int);
	void UTIL_SetRoamStatus(int);
	void UTIL_SetScreensaverStatus(int);
	void UTIL_SetScreensaverTimer(int);
	void UTIL_SetSecurityKeyLockState(int);
	void UTIL_SetServiceName(char s[61]);
	void UTIL_SetSideKeyLock(int);
	void UTIL_SetSignalQuality(int);
	void UTIL_SetSimCardChangedStatus(int);
	void UTIL_SetSimCardStatus(int);
	void UTIL_SetSimLock(int);
	void UTIL_SetSIMPlayTone(int);
	void UTIL_SetSliderStatus(int);
	void UTIL_SetSpeakerPhoneSetting(int);
	void UTIL_SetSpnDisplayedStatus(bool);
	void UTIL_SetSpnName(char s[61]);
	void UTIL_SetSTKSetupMenuStatus(int);
	void UTIL_SetSubsidyStatus(int);
	void UTIL_SetTalkingPhoneStatus(int);
	void UTIL_SetThemeInfo(int);
	void UTIL_SetTimeFormat(int);
	void UTIL_SetTimingPhoneLock(int);
	void UTIL_SetTotalDataBytes(int);
	void UTIL_SetTotalDuration(int);
	void UTIL_SetTPSoundInfo(int);
	void UTIL_SetTransparency(int);
	void UTIL_SetTTYDeviceStatus(int);
	void UTIL_SetTZEnv(int);
	void UTIL_SetUNSwitchStatus(int);
	void UTIL_SetUSBChargingStatus(int);
	void UTIL_SetUSBConnectionStatus(int);
	void UTIL_SetUSBDeviceType(int);
	void UTIL_SetUsbMassStorage(int);
	void UTIL_SetVerifyPin1Status(int);
	void UTIL_SetVRSupporting(int);
	void UTIL_SetWidgetPriority(QWidget*, int);
	void UTIL_SetWidgetSkinnableProp(int);
	void UTIL_SetWifiCampStatus(int);
	void UTIL_SetWifiConnectionInProgress(int);
	void UTIL_SetWifiLingertime(int);
	#ifdef EZX_ZN5
	void UTIL_SetWifiLinkStatus(int);
	#endif
	void UTIL_SetWifiProfileName(char n[129]);
	void UTIL_SetWifiSignalBar(int);
	void UTIL_SetWifiUMALingertime(int);
	
	#ifdef EZX_Z6W
	void UTIL_SetCLIIdleStatus(int);
	#endif	

#ifdef __cplusplus
}
#endif

#endif
