
#include "stdio.h"
#include "net_terminal.h"
#include <time.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>

static int app_net_terminal_device_info_get(PDEV_INFO_T pstDevInfo);
static int app_net_terminal_device_status_get(PDEV_STATUS_T pstDevStatus);
static int app_net_terminal_vehicle_status_get(PVEH_STATUS_T pstVehStatus);
static int app_net_terminal_setting_status_get(PSETTING_T pstSetting);
static int app_net_terminal_touch_info(PTOUCH_INFO_T pstTouchInfo);
static int app_net_terminal_ceritfy_num();
static int app_net_terminal_ceritfy_get(unsigned int id, PCERITFY_T pCeritfy);
static int app_net_terminal_area_num();
static int app_net_terminal_area_get(unsigned int id, PAREA_T pArea);

int app_net_terminal_BSD_notify();
int app_net_terminal_certify_send(int cmd);

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
	pAdapter->get_ceritfy_Num = app_net_terminal_ceritfy_num;
	pAdapter->get_ceritfy = app_net_terminal_ceritfy_get;
	pAdapter->get_area_Num = app_net_terminal_area_num;
	pAdapter->get_area = app_net_terminal_area_get;

	net_termianl_init();
	return 0;
}

char gps[] = {
	0x24, 0x47, 0x4e, 0x47, 0x47, 0x41, 0x2c, 0x30, 0x31, 0x34, 0x30, 0x30, 0x36, 0x2e, 0x30, 0x30, 0x30, 0x2c, 0x33, 0x30, 0x31, 0x31, 0x2e, 0x32, 0x34, 0x37,
	0x35, 0x39, 0x2c, 0x4e, 0x2c, 0x31, 0x32, 0x30, 0x31, 0x32, 0x2e, 0x32, 0x39, 0x34, 0x31, 0x35, 0x2c, 0x45, 0x2c, 0x31, 0x2c, 0x30, 0x39, 0x2c, 0x31, 0x2e,
	0x35, 0x2c, 0x34, 0x30, 0x2e, 0x38, 0x2c, 0x4d, 0x2c, 0x30, 0x2e, 0x30, 0x2c, 0x4d, 0x2c, 0x2c, 0x2a, 0x34, 0x35, 0x0d, 0x24, 0x47, 0x4e, 0x52, 0x4d, 0x43,
	0x2c, 0x30, 0x31, 0x34, 0x30, 0x30, 0x36, 0x2e, 0x30, 0x30, 0x30, 0x2c, 0x41, 0x2c, 0x33, 0x30, 0x31, 0x31, 0x2e, 0x32, 0x34, 0x37, 0x35, 0x39, 0x2c, 0x4e,
	0x2c, 0x31, 0x32, 0x30, 0x31, 0x32, 0x2e, 0x32, 0x39, 0x34, 0x31, 0x35, 0x2c, 0x45, 0x2c, 0x31, 0x2e, 0x32, 0x34, 0x2c, 0x32, 0x38, 0x33, 0x2e, 0x33, 0x35,
	0x2c, 0x30, 0x39, 0x30, 0x36, 0x32, 0x31, 0x2c, 0x2c, 0x2c, 0x41, 0x2a, 0x37, 0x32, 0x0d};

void gps_send(void *arg)
{
	while (1)
	{
		net_terminal_pushGPS(gps, sizeof(gps));
		//usleep(300000);
		sleep(1);
	}
}

int main(int argc, char const *argv[])
{

	app_net_terminal_init();

	pthread_t handle;
	pthread_create(&handle, NULL, &gps_send, (void*)handle);

	while(1)
	{
		int cmd, operate;
		printf("please input cmd...\n");

		scanf("%d %d", &cmd, &operate);
		switch (cmd)
		{
		case 0:
			app_net_terminal_BSD_notify();
			break;
		case 1:
			app_net_terminal_certify_send(operate);
			break;
		default:
			printf("*********************************\n");
			printf("usage: \n");
			printf("0 BSD notify\n");
			printf("1 certify notify\n");
			printf("*********************************\n");
			break;
		}
		sleep(2);
	}
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

int app_net_terminal_certify_send(int cmd)
{
	char msg[sizeof(MSG_HDR_T) + sizeof(CERITFY_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2803;

	PCERITFY_T pCeritfy = (PCERITFY_T)(msg + sizeof(MSG_HDR_T));
	if (cmd == 0)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 1;
		pCeritfy->id = 0;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "星环集团基础建设三局,A3L-11B,土卫六第三转移轨道,CN1718546,环日加速器改造工程", sizeof(pCeritfy->detail) - 1);
	}
	else if (cmd == 1)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 1;
		pCeritfy->id = 1;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "深空矿业,5376852485,CN1718546", sizeof(pCeritfy->detail) - 1);
	}
	else if (cmd == 2)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 1;
		pCeritfy->id = 2;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "环日加速器改造工程,土卫六,星环集团基础建设三局,深空矿业,深空矿业,土卫六,CN1718546,土卫六第三转移轨道", sizeof(pCeritfy->detail) - 1);
		
	}
	else if (cmd == 3)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 1;
		pCeritfy->id = 3;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "土卫六,A3L-11B,土卫六第三转移轨道,CN1718546,环日加速器改造工程,2051-07-01 20:12:33-2051-07-01 23:12:33,BT1718546,地球联邦", sizeof(pCeritfy->detail) - 1);
	}
	else
	{
		return -1;
	}
	pCeritfy->len = strlen(pCeritfy->detail) + 1;

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CERITFY_T)))
	{
		printf("send certify success\n");
		return 0;
	}
	else
	{
		printf("send certify fail!\n");
		return -1;
	}
}

static int app_net_terminal_ceritfy_num()
{
	return 4;
}

static int app_net_terminal_ceritfy_get(unsigned int id, PCERITFY_T pCeritfy)
{
	if (id == 0)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 0;
		pCeritfy->id = 0;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "星环集团基础建设三局,A3L-11B,土卫六第三转移轨道,CN1718546,环日加速器改造工程", sizeof(pCeritfy->detail) - 1);
	}
	else if (id == 1)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 1;
		pCeritfy->id = 1;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "深空矿业,5376852485,CN1718546", sizeof(pCeritfy->detail) - 1);
	}
	else if (id == 2)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 2;
		pCeritfy->id = 2;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "环日加速器改造工程,土卫六,星环集团基础建设三局,深空矿业,深空矿业,土卫六,CN1718546,土卫六第三转移轨道", sizeof(pCeritfy->detail) - 1);
		
	}
	else if (id == 3)
	{
		pCeritfy->operate = 0;
		pCeritfy->type = 3;
		pCeritfy->id = 3;
		pCeritfy->startTime = 2572599470;
		pCeritfy->endTime = 2604394670;
		 
		strncpy(pCeritfy->detail, "土卫六,A3L-11B,土卫六第三转移轨道,CN1718546,环日加速器改造工程,2051-07-01 20:12:33-2051-07-01 23:12:33,BT1718546,地球联邦", sizeof(pCeritfy->detail) - 1);
	}
	else
	{
		return -1;
	}
	
	pCeritfy->len = strlen(pCeritfy->detail) + 1;

	return 0;
}

static int app_net_terminal_area_num()
{
	return 4;
}

static int app_net_terminal_area_get(unsigned int id, PAREA_T pArea)
{
	return -1;
}