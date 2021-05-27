#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "net_terminal.h"

using DevInfo_t = DEV_INFO_T;
using PtrDevInfo_t = DEV_INFO_T;
using DevStatus_t = DEV_STATUS_T;
using PtrDevStatus_t = PDEV_STATUS_T;
using VehStatus_t = VEH_STATUS_T;
using PtrVehStatus_t = PVEH_STATUS_T;
using Setting_t = SETTING_T;
using PtrSetting_t = PSETTING_T;
using TouchInfo_t = TOUCH_INFO_T;
using PtrTouchInfo_t = PTOUCH_INFO_T;

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
	bool getSetting(Setting_t* pstSetting);
	bool sendTouchInfo(TouchInfo_t* pstTouchInfo);

private:
	AdptrFun_t m_adapter;
};

#endif //__ADAPTER_H__

