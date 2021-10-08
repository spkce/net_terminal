#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "net_terminal.h"

using DevInfo_t = DEV_INFO_T;
using PtrDevInfo_t = DEV_INFO_T;
using AudioInfo_t = AUDIO_INFO_T;
using PtrAudioInfo_t = PAUDIO_INFO_T;
using LedInfo_t = LED_INFO_T;
using PtrLedInfo_t = PLED_INFO_T;
using DevStatus_t = DEV_STATUS_T;
using PtrDevStatus_t = PDEV_STATUS_T;
using VehStatus_t = VEH_STATUS_T;
using PtrVehStatus_t = PVEH_STATUS_T;
using PeriStatus_t = PERI_STATUS_T;
using PtrPeriStatus_t = PPERI_STATUS_T;
using CarStatus_t = CAR_STA_T;
using PtrCarStatus_t = PCAR_STA_T;
using Setting_t = SETTING_T;
using PtrSetting_t = PSETTING_T;
using TouchInfo_t = TOUCH_INFO_T;
using PtrTouchInfo_t = PTOUCH_INFO_T;
using MsgHdr_t = MSG_HDR_T;
using PtrMsgHdr_t = PMSG_HDR_T;
using WarnInfo_t = WARN_INFO_T;
using PtrWarnInfo_t = PWARN_INFO_T;
using FaceInfo_t = FACE_INFO_T;
using PtrFaceInfo_t = PFACE_INFO_T;
using AlarmInfo_t = ALARM_INFO_T;
using PtrAlarmInfo_t = PALARM_INFO_T;
using PhotoTaken_t = PHOTO_TAKEN_T;
using FaceContrast_t = FACE_CONTRAST_T;
using PtrFaceContrast_t = PFACE_CONTRAST_T;
using PtrPhotoTaken_t = PPHOTO_TAKEN_T;
using Notification_t = NOTIFICATION_T;
using PtrNotification_t = PNOTIFICATION_T;
using CheckInfo_t = CHECk_INFO_T;
using PtrCheckInfo_t = PCHECk_INFO_T;
using MessageInfo_t = MESSAGE_INFO_T;
using PtrMessageInfo_t = PMESSAGE_INFO_T;
using Ceritfy_t = CERITFY_T;
using PtrCeritfy_t = PCERITFY_T;
using AreaInfo_t = AREA_INFO_T;
using PtrAreaInfo_t = PAREA_INFO_T;
using FileCriteria_t = FILE_CRITERIA_T;
using PtrFileCriteria_t = PFILE_CRITERIA_T;
using FileInfo_t = FILE_INFO_T;
using PtrFileInfo_t = PFILE_INFO_T;
using FtpSrvInfo_t = FTP_SERVER_INFO_T;
using PtrFtpSrvInfo_t = PFTP_SERVER_INFO_T;

using AdptrFun_t = ADAPTER_T;
using PtrAdptrFun_t = ADAPTER_T;

class CAdapter
{
private:
	CAdapter();
	~CAdapter();
public:
	static CAdapter* instance();
	AdptrFun_t* getAdapter();
	bool getDeviceInfo(DevInfo_t* pdevInfo);
	bool getAudioAlarmInfo(AudioInfo_t* pInfo);
	bool getLedScreenInfo(LedInfo_t* pInfo);
	bool getDeviceStatus(DevStatus_t* pdevStatus);
	bool getVehicleStatus(VehStatus_t* pVehStatus);
	bool getPeripheralStatus(PeriStatus_t* pPeriStatus);
	bool getCarStatus(CarStatus_t* pCarStatus);
	bool getSetting(Setting_t* pstSetting);
	bool sendTouchInfo(TouchInfo_t* pstTouchInfo);
	int getFaceNum();
	bool getFaceInfo(int index, FaceInfo_t* pInfo);
	bool setFaceInfo(int index, FaceInfo_t* pInfo);
	bool faceContrast(const char* pic);
	bool takePhoto(int channel, int type);
	bool checkSelf();
	int getCeritfyNum();
	bool getCeritfy(unsigned int id, Ceritfy_t* pCeritfy);
	bool upgradeResult(unsigned int result, unsigned int progress);
	void* getFileList(unsigned int type, FileCriteria_t* pCriteria, unsigned int* pNum);
	bool searchFileNext(int reverse, void *pHandle, FileInfo_t* pFileInfo);
	bool searchHandleRelease(void *pHandle);
	const char* getStringFile();
private:
	AdptrFun_t m_adapter;
};

#endif //__ADAPTER_H__

