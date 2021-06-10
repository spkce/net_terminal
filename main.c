
#include "stdio.h"
#include "net_terminal.h"
#include <time.h>
#include <string.h>

static int app_net_terminal_device_info_get(PDEV_INFO_T pstDevInfo);
static int app_net_terminal_device_status_get(PDEV_STATUS_T pstDevStatus);
static int app_net_terminal_vehicle_status_get(PVEH_STATUS_T pstVehStatus);
static int app_net_terminal_setting_status_get(PSETTING_T pstSetting);
static int app_net_terminal_touch_info(PTOUCH_INFO_T pstTouchInfo);

/**
 * @brief 初始化外部终端模块
 * @return 成功，返回OK；失败，返回-1
 */
int app_net_terminal_init()
{
	PADAPTER_T pAdapter = net_terminal_adapter_get();
	if (pAdapter == NULL)
	{
		return -1;
	}

	pAdapter->device_info_get = app_net_terminal_device_info_get;
	pAdapter->device_status_get = app_net_terminal_device_status_get;
	pAdapter->vehicle_status_get = app_net_terminal_vehicle_status_get;
	pAdapter->setting_get = app_net_terminal_setting_status_get;
	pAdapter->send_touch_info = app_net_terminal_touch_info;

	net_termianl_init();
	return 0;
}

int main(int argc, char const *argv[])
{

	app_net_terminal_init();

	while(1);
	return 0;
}

int app_net_terminal_device_info_get(PDEV_INFO_T pstDevInfo)
{
	strncpy(pstDevInfo->sDeviceType, "AE-AC3160-A", sizeof(pstDevInfo->sDeviceType));
	strncpy(pstDevInfo->sFirmVersion, "V1.0.1", sizeof(pstDevInfo->sFirmVersion));
	strncpy(pstDevInfo->sFirmDate, "2021.05.01", sizeof(pstDevInfo->sFirmDate));
	strncpy(pstDevInfo->sParamVersion, "V2.2.1", sizeof(pstDevInfo->sParamVersion));
	strncpy(pstDevInfo->sSerialNum, "F19484720", sizeof(pstDevInfo->sSerialNum));
	strncpy(pstDevInfo->sVerifyCode, "PJDACD", sizeof(pstDevInfo->sVerifyCode));
	strncpy(pstDevInfo->sCustomID, "TRUNKA3ZT", sizeof(pstDevInfo->sCustomID));
	strncpy(pstDevInfo->sHardwareVer, "V1.1.0", sizeof(pstDevInfo->sHardwareVer));
	strncpy(pstDevInfo->sMCUVer, "HK-MCUA3-SW-V1.1-20210526", sizeof(pstDevInfo->sMCUVer));
	strncpy(pstDevInfo->sDspVer, "V2.1 build210531", sizeof(pstDevInfo->sDspVer));
	strncpy(pstDevInfo->sFpgaVer, "V2.6.0 build210316", sizeof(pstDevInfo->sFpgaVer));
	strncpy(pstDevInfo->sGpsVer, "URANUS5,V5.2.1.0", sizeof(pstDevInfo->sGpsVer));
	return 0;
}

int app_net_terminal_device_status_get(PDEV_STATUS_T pstDevStatus)
{
	pstDevStatus->accStatus = 1;
	pstDevStatus->locationStatus = 1;
	pstDevStatus->CSQ = 1;

	time_t now;
	struct tm data;
	
	time(&now);
	localtime_r(&now, &data);

	snprintf(pstDevStatus->curTime, sizeof(pstDevStatus->curTime), "%4d-%02d-%02d %02d:%02d:%02d", data.tm_year + 1900, 
		data.tm_mon + 1, data.tm_mday, data.tm_hour, data.tm_min, data.tm_sec);

	pstDevStatus->bizPIfLoginStatus = 1;
	return 0;
}

int app_net_terminal_vehicle_status_get(PVEH_STATUS_T pstVehStatus)
{
	pstVehStatus->gear = 1;
	pstVehStatus->carryStatus = 0;
	pstVehStatus->hermeticStatus = 0;
	pstVehStatus->liftStatus = 1;
	pstVehStatus->lockStatus = 1;
	pstVehStatus->speedLimitStatus = 1;
	pstVehStatus->liftLimitStatus = 1;
	pstVehStatus->speedLimitThreshold = 120;
	pstVehStatus->maintainMode = 1;
	pstVehStatus->feedProtection = 1;
	return 0;
}
int app_net_terminal_setting_status_get(PSETTING_T pstSetting)
{
	time_t now;
	struct tm data;
	
	time(&now);
	localtime_r(&now, &data);

	snprintf(pstSetting->sTime, sizeof(pstSetting->sTime), "%4d-%02d-%02d %02d:%02d:%02d", data.tm_year + 1900, 
		data.tm_mon + 1, data.tm_mday, data.tm_hour, data.tm_min, data.tm_sec);
	
	return 0;

}

int app_net_terminal_touch_info(PTOUCH_INFO_T pstTouchInfo)
{
	return 0;
}

int app_net_terminal_BSD_notify()
{
	
	char msg[sizeof(MSG_HDR_T) + sizeof(WARN_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	PWARN_INFO_T pInfo = (PWARN_INFO_T)(msg + sizeof(WARN_INFO_T));
	phdr->msgID = 2807;

	pInfo->type = 4;

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(WARN_INFO_T)))
	{
		return 0;
	}

	return -1;
}
