#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "net_terminal.h"

using DevInfo_t = DEV_INFO_T;
using PtrDevInfo_t = DEV_INFO_T;
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
using AadaAlarm_t = ADAS_INFO_T;
using PtrAadaAlarm_t = PADAS_INFO_T;
using PhotoTaken_t = PHOTO_TAKEN_T;
using PtrPhotoTaken_t = PPHOTO_TAKEN_T;
using Notification_t = NOTIFICATION_T;
using PtrNotification_t = PNOTIFICATION_T;
using CheckInfo_t = CHECk_INFO_T;
using PtrCheckInfo_t = PCHECk_INFO_T;
using MessageInfo_t = MESSAGE_INFO_T;
using PtrMessageInfo_t = PMESSAGE_INFO_T;

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
	bool getDeviceStatus(DevStatus_t* pdevStatus);
	bool getVehicleStatus(VehStatus_t* pVehStatus);
	bool getPeripheralStatus(PeriStatus_t* pPeriStatus);
	bool getCarStatus(CarStatus_t* pCarStatus);
	bool getSetting(Setting_t* pstSetting);
	bool sendTouchInfo(TouchInfo_t* pstTouchInfo);
	int getFaceNum();
	bool getFaceInfo(unsigned int index, FaceInfo_t* pInfo);
	bool setFaceInfo(int index, FaceInfo_t* pInfo);
	bool takePhoto(int channel, int type);
	bool checkSelf();

private:
	AdptrFun_t m_adapter;
};

#endif //__ADAPTER_H__

