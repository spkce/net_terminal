
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

int app_net_terminal_BSD_notify();

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
		int cmd;
		printf("please input cmd...\n");

		scanf("%d", &cmd);
		switch (cmd)
		{
		case 0:
			app_net_terminal_BSD_notify();
			break;
		
		default:
			printf("usage: \n");
			printf("0 BSD notify\n");
			break;
		}
		
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

#if 0

/**@file    app_net_terminal.c
 * @note    Hangzhou Hikvision Automotive Technology Co., Ltd. All Right Reserved.
 * @brief   外部终端模块
 *
 * @author  yanggen5
 * @date    2021-5-28
 */
#ifdef CONFIG_NET_TERMINAL
#include "sys_common.h"
#include "app_private.h"
#include "net_terminal.h"
#include "jt808_platform.h"
#include "../lcd_ui/lcd_sqlite_private.h"
#ifdef CONFIG_FACE
#include "face.h"
#endif

/*
 *@brief 判断返回值是否为0，不为0，输出一段打印后返回一个值
 */
#define CHECK_VALUE_RET(x, PRINTF, RET)                        \
	do                                                         \
	{                                                          \
		if ((x) < (0))                                         \
		{                                                      \
			PRINTF("[%s]return error, %d\n", __FUNCTION__, x); \
			return RET;                                        \
		}                                                      \
	} while (0)

static INT32 app_net_terminal_device_info_get(PDEV_INFO_T pstDevInfo);
static INT32 app_net_terminal_device_status_get(PDEV_STATUS_T pstDevStatus);
static INT32 app_net_terminal_vehicle_status_get(PVEH_STATUS_T pstVehStatus);
static INT32 app_net_terminal_setting_status_get(PSETTING_T pstSetting);
static INT32 app_net_terminal_touch_info(PTOUCH_INFO_T pstTouchInfo);
static INT32 app_net_terminal_car_status_get(PCAR_STA_T pCarStatus);
static INT32 app_net_terminal_get_face_num(VOID);
static INT32 app_net_terminal_get_face_Info(int index, PFACE_INFO_T pInfo);
static INT32 app_net_terminal_set_face_Info(int index, PFACE_INFO_T pInfo);
static INT32 app_net_terminal_take_photo(int channel, int type);
static INT32 app_net_terminal_get_peripheral_status(PPERI_STATUS_T pstPeriStatus);
static INT32 app_net_terminal_checkSelf(VOID);
static INT32 app_net_terminal_ceritfy_num(VOID);
static INT32 app_net_terminal_ceritfy_get(UINT32 id, PCERITFY_T pCeritfy);
static INT32 app_net_terminal_area_num(VOID);
static INT32 app_net_terminal_area_get(UINT32 id, PAREA_T pArea);

/**
 * @brief 初始化外部终端模块
 * @return 成功，返回OK；失败，返回ERROR
 */
INT32 app_net_terminal_init(VOID)
{
	PADAPTER_T pAdapter = net_terminal_adapter_get();
	if (pAdapter == NULL)
	{
		APP_CORE_ERROR("get Adapter fail!\n");
		return ERROR;
	}

	pAdapter->device_info_get = app_net_terminal_device_info_get;
	pAdapter->device_status_get = app_net_terminal_device_status_get;
	pAdapter->vehicle_status_get = app_net_terminal_vehicle_status_get;
	pAdapter->car_status_get = app_net_terminal_car_status_get;
	pAdapter->setting_get = app_net_terminal_setting_status_get;
	pAdapter->send_touch_info = app_net_terminal_touch_info;
	pAdapter->get_face_total_number = app_net_terminal_get_face_num;
	pAdapter->get_face_info = app_net_terminal_get_face_Info;
	pAdapter->set_face_info = app_net_terminal_set_face_Info;
	pAdapter->take_photo = app_net_terminal_take_photo;
	pAdapter->peripheral_status_get = app_net_terminal_get_peripheral_status;
	pAdapter->checkSelf = app_net_terminal_checkSelf;
	pAdapter->get_ceritfy_Num = app_net_terminal_ceritfy_num;
	pAdapter->get_ceritfy = app_net_terminal_ceritfy_get;
	pAdapter->get_area_Num = app_net_terminal_area_num;
	pAdapter->get_area = app_net_terminal_area_get;

	net_termianl_init();
	return OK;
}

/**
 * @brief  获取设备信息
 * @param  pstDevInfo 获取的参数结构体指针
 * @return 成功返回 OK；失败返回 ERROR
 **
 */
static INT32 app_net_terminal_device_info_get(PDEV_INFO_T pstDevInfo)
{
	INT32 iRet = OK;
	UINT32 uValue = 0;
	UINT32 uMain = 0;
	UINT32 uSub = 0;
	UINT32 uYear = 0;
	UINT32 uMon = 0;
	UINT32 uDay = 0;
	CHAR *sFirst = NULL;
	CHAR *sSecond = NULL;
	CHAR sVersionBuf[32] = {0};

	SYS_CHECK_PTR_RET(pstDevInfo, APP_CORE_ERROR, ERROR);

	iRet = capa_model_strings_get((UINT8 *)pstDevInfo->sDeviceType, NET_APP_DEV_INFO_LEN);
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);

	iRet = capa_serial_num_get((UINT8 *)pstDevInfo->sSerialNum, NET_APP_DEV_INFO_LEN);
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);

	iRet = capa_verify_code_get((UINT8 *)pstDevInfo->sVerifyCode, NET_APP_DEV_INFO_LEN > VERRIFY_NO_LEN ? (VERRIFY_NO_LEN) : NET_APP_DEV_INFO_LEN);
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);
	pstDevInfo->sVerifyCode[strlen(pstDevInfo->sVerifyCode)] = '\0';

	iRet = cap_custom_model_type_get((UINT8 *)pstDevInfo->sCustomID, NET_APP_DEV_INFO_LEN);
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);

	uValue = capa_language_get();
	switch (uValue)
	{
	case SYS_LANGUAGE_EN:
		pstDevInfo->uLanguage = 0;
		break;
	case SYS_LANGUAGE_CH:
		pstDevInfo->uLanguage = 1;
		break;
	default:
		APP_CORE_ERROR("device language error!\n");
		return ERROR;
	}

	memset(sVersionBuf, 0, sizeof(sVersionBuf));
	iRet = app_version(sVersionBuf, sizeof(sVersionBuf));
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);

	iRet = capa_hardware_version_get();
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);
	snprintf(pstDevInfo->sHardwareVer, sizeof(pstDevInfo->sHardwareVer), "V%d.%d", ((iRet) / 10 + 1), ((iRet) % 10));

	sFirst = strtok_r(sVersionBuf, " ", &sSecond);
	SYS_CHECK_PTR_RET(sFirst, APP_CORE_ERROR, ERROR);

	snprintf(pstDevInfo->sFirmVersion, sizeof(pstDevInfo->sFirmVersion), "%s", sFirst);

	snprintf(pstDevInfo->sFirmDate, sizeof(pstDevInfo->sFirmDate), "%s", sSecond);

	snprintf(pstDevInfo->sParamVersion, sizeof(pstDevInfo->sParamVersion), "%s", sFirst);

	memset(sVersionBuf, 0, sizeof(sVersionBuf));
	iRet = mcu_soft_version_get(sVersionBuf, sizeof(sVersionBuf));
	snprintf(pstDevInfo->sMCUVer, sizeof(pstDevInfo->sMCUVer), "%s", sVersionBuf);

	memset(sVersionBuf, 0, sizeof(sVersionBuf));
	iRet = mcu_gps_version_get(sVersionBuf, sizeof(sVersionBuf));
	snprintf(pstDevInfo->sGpsVer, sizeof(pstDevInfo->sGpsVer), "%s", sVersionBuf);

	iRet = dsp_mod_version(DSP_MOD_VERSION_DSP, &uMain, &uSub, &uYear, &uMon, &uDay);
	if (iRet != OK)
	{
		APP_CORE_ERROR("get dsp version failed\n");
		return ERROR;
	}
	snprintf(pstDevInfo->sDspVer, sizeof(pstDevInfo->sDspVer), "V%d.%d build%d%02d%02d", uMain, uSub, uYear, uMon, uDay);

	iRet = dsp_mod_version(DSP_MOD_VERSION_ZYNQ, &uMain, &uSub, &uYear, &uMon, &uDay);
	if (iRet != OK)
	{
		APP_CORE_ERROR("get fpga version failed\n");
		return ERROR;
	}
	snprintf(pstDevInfo->sFpgaVer, sizeof(pstDevInfo->sFpgaVer), "V%d.%d.%d build%d%02d%02d", uMain, uSub & 0xFF, (uSub >> 8) & 0xFF, uYear, uMon, uDay);

	return iRet;
}

/**
 * @brief  获取设备状态
 * @param  pstDevInfo 获取的设备状态结构体指针
 * @return 成功返回 OK；失败返回 ERROR
 */
static INT32 app_net_terminal_device_status_get(PDEV_STATUS_T pstDevStatus)
{
	SYS_CHECK_PTR_RET(pstDevStatus, APP_CORE_ERROR, ERROR);

	/*acc状态*/
	switch (mcu_info_acc_status())
	{
	case MCU_ACC_ON:
		pstDevStatus->accStatus = 1;
		break;
	case MCU_ACC_OFF:
		pstDevStatus->accStatus = 0;
		break;
	default:
		pstDevStatus->accStatus = -1;
		APP_CORE_WARN("get acc status error!\n");
		break;
	}

	//gps
	GPS_DATA_T stGpsData = {0};
	if (gps_data_get(&stGpsData, sizeof(GPS_DATA_T)) == ERROR)
	{
		APP_CORE_WARN("get gps data error!\n");
		pstDevStatus->locationStatus = -1;
	}
	else
	{
		pstDevStatus->locationStatus = (int)stGpsData.bValid;
	}

	//网络信号强度
	DIAL_STATUS_T *pStDialStatus = dial_ctrl_get_state();
	SYS_CHECK_PTR_RET(pStDialStatus, APP_CORE_ERROR, ERROR);
	pstDevStatus->CSQ = pStDialStatus->iCsqVal;

	//时间
	SYS_DATE_TIME_T stSysTime = {0};
	INT32 iRet = sys_datetime_get(&stSysTime);
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);
	snprintf(pstDevStatus->curTime, NET_APP_DATE_LEN, "%4d-%02d-%02d %02d:%02d:%02d", stSysTime.uYear,
			 stSysTime.uMonth, stSysTime.uDay, stSysTime.uHour, stSysTime.uMinute, stSysTime.uSec);

	//业务平台固定为 2或3号平台
	pstDevStatus->bizPIfLoginStatus = (int)((jt808_is_online(2) == 1) || (jt808_is_online(1) == 1));

	return OK;
}

/**
 * @brief  获取车辆状态
 * @param  pstVehStatus 获取的车辆状态结构体指针
 * @return 成功返回 OK；失败返回 ERROR
 */
static INT32 app_net_terminal_vehicle_status_get(PVEH_STATUS_T pstVehStatus)
{
	SYS_CHECK_PTR_RET(pstVehStatus, APP_CORE_ERROR, ERROR);

	/*挡位*/
	//倒车>右转弯>左转弯*/
	UINT16 usGear = 0;
	BOOL bRight = 0;
	BOOL bLeft = 0;
	BOOL back = 0;
	app_veh_gear_get(&usGear);
	app_veh_turn_get(&bLeft, &bRight);
	back = app_veh_back_off_get();
	if (back || (4 == usGear))
	{
		pstVehStatus->gear = 16; //倒挡
	}
	else if (bRight)
	{
		pstVehStatus->gear = 18; //右转
	}
	else if (bLeft)
	{
		pstVehStatus->gear = 17; // 左转
	}
	else if (usGear == 1)
	{
		pstVehStatus->gear = 1; // 前进挡[1,15]
	}
	else
	{
		pstVehStatus->gear = -1;
	}

#define EMPTY 0
#define HEAVY 1
#define OVER 2

	/*载货状态*/
	switch (app_veh_load_status_get())
	{
	case LOAD_EMPTY_STATUS:
		pstVehStatus->carryStatus = EMPTY;
		break;
	case LOAD_HEAVY_STATUS:
	case LOAD_FULL_STATUS:
	case LOAD_LIGHT_STATUS:
		pstVehStatus->carryStatus = HEAVY;
		break;
	case LOAD_SUPER_STATUS:
		pstVehStatus->carryStatus = OVER;
		break;
	default:
		pstVehStatus->carryStatus = -1;
		APP_CORE_WARN("get carry status error!\n");
		break;
	}

	/*密闭状态*/
	pstVehStatus->hermeticStatus = (int)(app_veh_cover_status_get() == 2);

	/*举升状态*/
	pstVehStatus->liftStatus = (int)(app_veh_lift_status_get() == 1);

	CURRENT_LIMT_STATE_T *VehCtrl = vehicle_limt_state_get();
	SYS_CHECK_PTR_RET(VehCtrl, APP_CORE_ERROR, ERROR);

	/*车辆锁车*/
	if (VehCtrl->uclock && (VehCtrl->uctrl & 0x01))
	{
		pstVehStatus->lockStatus = 1;
	}

	/*车辆限速*/
	if (VehCtrl->uclimtspeed && (VehCtrl->uctrl & 0x02))
	{
		pstVehStatus->speedLimitStatus = 1;
	}

	/*车辆限举*/
	if (VehCtrl->uclimtlift && (VehCtrl->uctrl & 0x04))
	{
		pstVehStatus->liftLimitStatus = 1;
	}

	/*车辆限速值*/
	if (VehCtrl->uclimtspeed && (VehCtrl->uctrl & 0x02))
	{
		pstVehStatus->speedLimitThreshold = VehCtrl->uclimtspeed;
	}
	else
	{
		pstVehStatus->speedLimitThreshold = -1;
	}

	/*维护模式*/
	if (!VehCtrl->uctrl)
	{
		pstVehStatus->maintainMode = 1;
	}

	/*馈电保护*/
	pstVehStatus->feedProtection = 1;

	return OK;
}

/**
 * @brief  获取设置参数
 * @param  pstSetting 获取的设置参数结构体指针 目前只支持时间
 * @return 成功返回 OK；失败返回 ERROR
 */
static INT32 app_net_terminal_setting_status_get(PSETTING_T pstSetting)
{
	SYS_CHECK_PTR_RET(pstSetting, APP_CORE_ERROR, ERROR);

	//时间
	SYS_DATE_TIME_T stSysTime = {0};
	INT32 iRet = sys_datetime_get(&stSysTime);
	CHECK_VALUE_RET(iRet, APP_CORE_ERROR, ERROR);
	snprintf(pstSetting->sTime, NET_APP_DATE_LEN, "%4d-%02d-%02d %02d:%02d:%02d", stSysTime.uYear,
			 stSysTime.uMonth, stSysTime.uDay, stSysTime.uHour, stSysTime.uMinute, stSysTime.uSec);

	return OK;
}

/**
 * @brief 触屏信息响应
 * @param  pstTouchInfo 触屏信息结构体指针
 * @return 成功返回 OK；失败返回 ERROR
 */
static INT32 app_net_terminal_touch_info(PTOUCH_INFO_T pstTouchInfo)
{
	static UINT32 uTouchTime = 0;
	//static UINT32 uLastTime = 0;
	static BOOL bAlarmStart = FALSE;
	static UINT8 uTouchNum = 0;
	static UINT32 uLastPosX = 0;
	static UINT32 ulastPosY = 0;
	SYS_CHECK_PTR_RET(pstTouchInfo, APP_CORE_ERROR, ERROR);
	/*目前仅支持默认6分屏触屏放大*/
	if (CVBS_SLIP_SIX != cfg_cvbs_show_mode_get())
	{
		APP_CORE_NOTE("touch screen support six clip\n");
		return OK;
	}

	UINT32 uPosXUint = (UINT32)(pstTouchInfo->screenWidth / 3);
	UINT32 uPosYUint = (UINT32)(pstTouchInfo->screenHeight / 3);
	UINT8 ucAreaPos = 0;

	/*根据区间划分区域事件*/
	if ((pstTouchInfo->touchX >= 0 && pstTouchInfo->touchX <= 2 * uPosXUint) && (pstTouchInfo->touchY >= 0 && pstTouchInfo->touchY <= 2 * uPosYUint))
	{
		ucAreaPos = LCD_SHOW_SCREEN_POS_LU_TYPE;
	}
	else if ((pstTouchInfo->touchX >= 2 * uPosXUint && pstTouchInfo->touchX <= 3 * uPosXUint) && (pstTouchInfo->touchY >= 0 && pstTouchInfo->touchY <= uPosYUint))
	{
		ucAreaPos = LCD_SHOW_SCREEN_POS_RU_TYPE;
	}
	else if ((pstTouchInfo->touchX >= 2 * uPosXUint && pstTouchInfo->touchX <= 3 * uPosXUint) && (pstTouchInfo->touchY >= uPosYUint && pstTouchInfo->touchY <= 2 * uPosYUint))
	{
		ucAreaPos = LCD_SHOW_SCREEN_POS_RM_TYPE;
	}
	else if ((pstTouchInfo->touchX >= 0 && pstTouchInfo->touchX <= uPosXUint) && (pstTouchInfo->touchY >= 2 * uPosYUint && pstTouchInfo->touchY <= 3 * uPosYUint))
	{
		ucAreaPos = LCD_SHOW_SCREEN_POS_LD_TYPE;
	}
	else if ((pstTouchInfo->touchX >= uPosXUint && pstTouchInfo->touchX <= 2 * uPosXUint) && (pstTouchInfo->touchY >= 2 * uPosYUint && pstTouchInfo->touchY <= 3 * uPosYUint))
	{
		ucAreaPos = LCD_SHOW_SCREEN_POS_MD_TYPE;
	}
	else if ((pstTouchInfo->touchX >= 2 * uPosXUint && pstTouchInfo->touchX <= 3 * uPosXUint) && (pstTouchInfo->touchY >= 2 * uPosYUint && pstTouchInfo->touchY <= 3 * uPosYUint))
	{
		ucAreaPos = LCD_SHOW_SCREEN_POS_RD_TYPE;
	}

	/*判断是否达到要求*/
	BOOL touchflag = FALSE;
	if (pstTouchInfo->touchType == 1)
	{
		/*两次单击时间间隔要小于该时间，否则不算双击*/
		if (sys_time_get() - uTouchTime >= TOUCH_EVENT_CHECK_TIME)
		{
			uTouchNum = 0;
		}

		uTouchNum++;
		uTouchTime = sys_time_get();

		/*双击两次触发切屏*/
		if ((uTouchNum == 2))
		{
			INT32 iDx = (INT32)(pstTouchInfo->touchX - uLastPosX);
			INT32 iDy = (INT32)(pstTouchInfo->touchY - ulastPosY);

			if (iDx * iDx + iDy * iDy < 50)
			{
				touchflag = TRUE;
			}

			uTouchNum = 0;
			//uLastTime = sys_time_get();
		}

		uLastPosX = pstTouchInfo->touchX;
		ulastPosY = pstTouchInfo->touchY;
	}

	if (touchflag)
	{
		/*事件使能控制*/
		bAlarmStart = !bAlarmStart;
		touchflag = FALSE;
		/*事件通知*/
		app_action_cvbs_event_notify(LCD_SHOW_TOUCH_SIG_TYPE, ucAreaPos, bAlarmStart);
		APP_CORE_NOTE("touch position is:%d\n", ucAreaPos);
	}
	return OK;
}

/**
 * @brief BSD报警信息通知
 * @param uType 报警类型
 * @param uSubType 报警子类型
 * @return 成功返回 OK；失败返回 ERROR
 */
INT32 app_net_terminal_bsd_notify(UINT32 uType, UINT32 uSubType)
{

	char msg[sizeof(MSG_HDR_T) + sizeof(WARN_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	PWARN_INFO_T pInfo = (PWARN_INFO_T)(msg + sizeof(MSG_HDR_T));
	phdr->msgID = 2807;

	if (uType == ALARM_TYPE_BSD_R)
	{
		pInfo->type = (int)uSubType + 1;
	}
	else if (uType == ALARM_TYPE_BSD_L)
	{
		pInfo->type = 4;
	}
	else
	{
		return ERROR;
	}

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(WARN_INFO_T)))
	{
		return OK;
	}

	return ERROR;
}

/**
 * @brief 发送GPS数据
 * @param pData :GPS 裸数据
 * @param uLen:数据长度
 * @return 成功，返回OK；失败，返回ERROR
 */
INT32 app_net_terminal_gps_push(INT8 *pData, INT32 len)
{
	return net_terminal_pushGPS(pData, len);
}

/**
 * @brief 获取车辆状态
 * @param pCarStatus :GPS 车辆状态
 * @return 成功，返回OK；失败，返回ERROR
 */
static INT32 app_net_terminal_car_status_get(PCAR_STA_T pCarStatus)
{
	if (pCarStatus == NULL)
	{
		return ERROR;
	}

	pCarStatus->brake = (int)app_veh_brake_get();

	BOOL bLeft = FALSE;
	BOOL bRight = FALSE;
	app_veh_turn_get(&bLeft, &bRight);

	if (bLeft == TRUE || bRight == FALSE)
	{
		pCarStatus->corneringLamp = 1;
	}
	else if (bLeft == FALSE || bRight == TRUE)
	{
		pCarStatus->corneringLamp = 2;
	}
	else if (bLeft == TRUE || bRight == TRUE)
	{
		pCarStatus->corneringLamp = 3;
	}
	else
	{
		pCarStatus->corneringLamp = 0;
	}

	return OK;
}

/**
 * @brief  获取特征库中人脸个数
 * @param pCarStatus :GPS 车辆状态
 * @return 特征库中人脸个数
 */
static INT32 app_net_terminal_get_face_num(VOID)
{
	UINT32 uFaceNum = 0;
#ifdef CONFIG_FACE
	if (face_user_face_num(&uFaceNum) != OK)
	{
		uFaceNum = 0;
	}
#endif
	return (INT32)uFaceNum;
}

/**
 * @brief 获取人脸路径
 * @param index :face id
 * @param pPath:路径缓冲
 * @param len:缓冲长度
 * @return 成功/失败
 */
INT32 find_face_path(int index, CHAR* pPath, unsigned int len)
{
	if (pPath == NULL)
	{
		return ERROR;
	}
#define MEDIA_NO 3
	INT8 i = 0;
	for (i = 0; i < MEDIA_NO; i++)
	{
		if (SYS_STOR_ONLINE == sys_storage_state_get(i))
		{
			if (i == 0)
			{
				snprintf(pPath, len, "/mnt/hda1/ID_%d.jpg", index);
				return OK;
			}
			else if (i == 1)
			{
				snprintf(pPath, len, "/mnt/hda1/ID_%d.jpg", index);
				return OK;
			}
			else
			{
				snprintf(pPath, len, "/mnt/hda1/ID_%d.jpg", index);
				return OK;
			}
		}
	}

	return ERROR;
}

/**
 * @brief 获取特征库中人脸信息
 * @return 成功/失败
 */
static INT32 app_net_terminal_get_face_Info(int index, PFACE_INFO_T pInfo)
{
	FACE_USER_INFO_T info = {0};
	if (face_user_info_get((UINT32)index, &info) != OK)
	{
		return ERROR;
	}

	pInfo->faceID = (int)index;
	strncpy(pInfo->name, (char *)info.szName, sizeof(pInfo->name) - 1);
	strncpy(pInfo->identityID, (char *)info.szDriverId, sizeof(pInfo->identityID) - 1);
	strncpy(pInfo->license, (char *)info.szCertId, sizeof(pInfo->license) - 1);

	return find_face_path(index, pInfo->path, sizeof(pInfo->path));
}

typedef struct
{
	BOOL bDone;
	UINT32 uPicLen;
	UINT32 uPicType;
	UINT8 szStartTime[64];
	UINT8 szPicPath[PATH_MAX_LEN];
	UINT8 szThmPath[PATH_MAX_LEN];
} CAPTURE_PARAM_T;

CAPTURE_PARAM_T g_capInfo = {0};

/**
 * @brief 传输抓图结果
 * @param pPicPath :抓图路径
 * @param uPicLen:抓图数据长度
 * @param iPicType:抓图类型
 * @param pStartTime:抓图时间
 * @param pThmPath:缩略图地址
 */
VOID app_net_terminal_snap_info(INT8 *pPicPath, INT32 uPicLen, INT32 iPicType, INT8 *pStartTime, INT8 *pThmPath)
{
	if (NULL == pPicPath || NULL == pStartTime || NULL == pThmPath)
	{
		APP_CORE_ERROR("app_net_terminal_snap_info param error!\n");
		return;
	}

	snprintf((CHAR *)g_capInfo.szPicPath, sizeof(g_capInfo.szPicPath), "%s", pPicPath);
	snprintf((CHAR *)g_capInfo.szStartTime, sizeof(g_capInfo.szStartTime), "%s", pStartTime);
	snprintf((CHAR *)g_capInfo.szThmPath, sizeof(g_capInfo.szThmPath), "%s", pThmPath);
	g_capInfo.uPicLen = uPicLen;
	g_capInfo.uPicType = iPicType;
	g_capInfo.bDone = TRUE;

	APP_CORE_NOTE("capture INFO:\npicPath:%s\npicStartTime:%s\nthmPath:%s\npicLen:%d\npicType:%d\n",
				  g_capInfo.szPicPath, g_capInfo.szStartTime, g_capInfo.szThmPath, g_capInfo.uPicLen, g_capInfo.uPicType);
}

static STATUS face_register(UINT8 *pJpegData, UINT32 uJpegSize, INT32 iFaceId)
{
#ifdef CONFIG_FACE
	UINT8 *pYuvBuf = NULL;
	UINT32 iYuvSize = SIZE_3MB;
	UINT32 uInnerID = 0;
	INT32 iRet = OK;
	
	if (NULL == pJpegData)
	{
		APP_CORE_ERROR("pHandle == NULL,error!\n");
		return ERROR;
	}
	/*因为face_jpeg_cmp和face_jpeg_reg都调用了jpeg_to_yuv函数，而这个函数可能会修改使用的图片数据，
          导致后面的操作失败，故这里需要临时拷贝一份备用*/
	pYuvBuf = (UINT8 *)sys_mem_alloc(iYuvSize);
	if (NULL == pYuvBuf)
	{
		APP_CORE_ERROR("malloc failed\n");
		return ERROR;
	}
	memset(pYuvBuf, 0, iYuvSize);
	memcpy(pYuvBuf, pJpegData, uJpegSize);

	/*若待注册人脸与临时人脸相似度很高，则删除临时人脸后再进行注册*/
	FACE_EVENT_INFO_T stInfo = {0};
	uInnerID = face_jpeg_cmp(pJpegData, uJpegSize, &stInfo);
	if (0 == uInnerID)
	{
		APP_MAIN_NOTE("reg face is similar to temp face,clear temp face!\n");
		/*清除临时人脸数据*/
		FACE_FEATURE_DATA_T *stFeat = NULL;
		stFeat = (FACE_FEATURE_DATA_T *)face_feat_ctrl_get();
		if (dsp_temp_face_feat_clear(stFeat) != OK)
		{
			APP_CORE_ERROR("clear temp face failed!\n");
		}
		else
		{
			APP_CORE_NOTE("temp face feat clear success\n");
		}
	}

	if (uInnerID != FACE_RET_JPEG_ERR)
	{
		iRet = face_jpeg_reg(pYuvBuf, uJpegSize, iFaceId);
	}
	SYS_SAFE_FREE(pYuvBuf);
#endif

	return iRet;
}

/**
 * @brief   安卓屏给设备设置人脸信息
 * @param uFaceId 司机ID
 * @param pUserInfo 人脸信息结构体
 * @return OK-配置成功,ERROR-配置失败
 */
static STATUS set_face_info(int faceID, PFACE_INFO_T pInfo)
{
#ifdef CONFIG_FACE
	FACE_USER_INFO_T stfaceUserInfo = {0};
	if (pInfo == NULL)
	{
		APP_CORE_ERROR("param NULL!\n");
		return ERROR;
	}

	//stfaceUserInfo.uDriverLastTime;//驾驶员最新变更时间

	stfaceUserInfo.uCertIDType = 1;
	stfaceUserInfo.uSource = 0;
	stfaceUserInfo.uCertIDLen = strlen(pInfo->license);
	strncpy((CHAR*)stfaceUserInfo.szCertId, pInfo->license, sizeof(stfaceUserInfo.szCertId));
	stfaceUserInfo.uNameLen = strlen(pInfo->name);
	strncpy((CHAR*)stfaceUserInfo.szName, pInfo->name, sizeof(stfaceUserInfo.szCertId));
	stfaceUserInfo.ucDriverLen = strlen(pInfo->identityID);
	strncpy((CHAR*)stfaceUserInfo.szDriverId, pInfo->identityID, sizeof(stfaceUserInfo.szDriverId));

	APP_CORE_NOTE("##uFaceId %d, name %s, cardID %s!!\n\n", faceID, stfaceUserInfo.szName, stfaceUserInfo.szCertId);

	if (ERROR == face_user_info_set(faceID, (FACE_USER_INFO_T *)&stfaceUserInfo))
	{
		APP_MAIN_FATAL("net screen face_jpeg_reg,error!\n");
		return ERROR;
	}
	return OK;
#else
	return ERROR;
#endif
	
}

/**
 * @brief 触发人脸抓图
 */
static INT32 app_net_terminal_snap(PFACE_INFO_T pInfo, PNOTIFICATION_T pNotify)
{
	BOOL isOK = FALSE;

	if (pInfo == NULL || pNotify == NULL)
	{
		goto snap_fail;
	}

#define SNAPINFO_TIMEOUT 30
	
	do
	{
		INT32 iTimeOut = 0;
		memset(&g_capInfo, 0, sizeof(g_capInfo));
		if (ERROR == app_record_start(SECOND_CHAN_NO, APP_RECORD_TYPE_FACE_PIC))
		{
			APP_MAIN_FATAL("app_record_start capture error!\n");
			goto snap_fail;
		}

		APP_MAIN_NOTE("ChanNo 2 capture success,wait for picture info\n");
		while (!g_capInfo.bDone)
		{
			sys_wait_msec(100);

			if (++iTimeOut >= SNAPINFO_TIMEOUT)
			{
				APP_MAIN_FATAL("wait for captue info ,timeout arrive 3 seconds,error!");
				memset(&g_capInfo, 0, sizeof(g_capInfo));
				goto snap_fail;
			}
		}
	} while (0);

	VOID* pPicHandle = app_record_open((CHAR*)g_capInfo.szPicPath);
	if (pPicHandle == NULL)
	{
		APP_CORE_ERROR("### fopen err, filepath = [%s] \n", g_capInfo.szPicPath);
		goto snap_fail;
	}

	UINT32 uFilesize = 0;
	if (app_record_size((CHAR*)g_capInfo.szPicPath, &uFilesize) == ERROR)
	{
		APP_CORE_ERROR("###:File is too long, size = [%d] \n", uFilesize);
		goto record_fail;
	}

	UINT8* pFileBuf = (UINT8 *)sys_mem_alloc(uFilesize);
	if (pFileBuf == NULL)
	{
		APP_CORE_ERROR("###capture_picture_upload :malloc failed!!!\n");
		goto record_fail;
	}
	bzero(pFileBuf, uFilesize);

	if (app_record_read(pPicHandle, pFileBuf, uFilesize) == 0)
	{
		APP_CORE_ERROR("###:fread err! \n");
		goto fail;
	}

	CHAR fileName[PATH_MAX_LEN] = {0};
	INT32 faceId = find_face_idle_id();

	if (find_face_path(faceId, fileName, sizeof(fileName))== ERROR)
	{
		APP_CORE_ERROR("get face file path err !\n");
		goto fail;
	}
	else
	{
		APP_CORE_NOTE("current need save file path %s.\n", fileName);
	}


	if (sys_file_exist(fileName) == OK)
	{
		sys_file_remove(fileName);
	}
	sys_save_file(fileName, pFileBuf, uFilesize);

	if (face_register(pFileBuf, uFilesize, faceId) == ERROR)
	{
		APP_CORE_ERROR("register face err ! \n");
	}else
	{
		if (set_face_info(faceId, pInfo) == ERROR)
		{
			APP_CORE_ERROR("set face info err ! \n");
		}
		else
		{
			isOK = TRUE;
		}
	}

fail:
	sys_mem_free(pFileBuf);
record_fail:
	app_record_close(pPicHandle);
snap_fail:

	if (isOK)
	{
		pNotify->photoTaken.filesize = uFilesize;
		pNotify->photoTaken.type = g_capInfo.uPicType;
		strncpy(pNotify->photoTaken.path, (char*)fileName, sizeof(pNotify->photoTaken.path));
		strncpy(pNotify->photoTaken.startTime, (char*)g_capInfo.szStartTime, sizeof(pNotify->photoTaken.startTime));
		strncpy(pNotify->photoTaken.thmPath, (char*)g_capInfo.szThmPath, sizeof(pNotify->photoTaken.thmPath));
		pNotify->photoTaken.result = 0;
		return OK;
	}

	return ERROR;
}

static VOID take_photo(MSG_Q_ID hande)
{
	INT32 iWaitTime = 1000;
	FACE_INFO_T faceInfo = {0};

	char msg[sizeof(MSG_HDR_T) + sizeof(NOTIFICATION_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	PNOTIFICATION_T pNotify = (PNOTIFICATION_T)(msg + sizeof(WARN_INFO_T));
	phdr->msgID = 601;
	strncpy(pNotify->type, "photoTaken", sizeof(pNotify->type));
	pNotify->photoTaken.result = 1;

	if(sys_mqueue_recv(&hande, (char *)&faceInfo, sizeof(FACE_INFO_T), iWaitTime) == sizeof(FACE_INFO_T))
	{
		/*切到第2通道单画面*/
		app_action_cvbs_event_notify(LCD_SHOW_TOUCH_SIG_TYPE, LCD_SHOW_FACE_REQ_TYPE, TRUE);
		audio_tip_audio_id_play_temp(ZT_COMMON_ALARM_AUDIO_CHAN, BEEP_VEHICLE_FACE_NOTIFY, ZT_COMMON_ALARM_AUDIO_VOLUMN);
		/*1s播放，等待5s，共6秒*/
		sys_wait_msec(6000);
		/*主动抓取人脸图片*/
		if (app_net_terminal_snap(&faceInfo, pNotify) == OK)
		{
			pNotify->photoTaken.result = 0;
		}
		/*结束切屏*/
		app_action_cvbs_event_notify(LCD_SHOW_TOUCH_SIG_TYPE, LCD_SHOW_FACE_REQ_TYPE, FALSE);
		
	}

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(NOTIFICATION_T)))
	{
		APP_CORE_NOTE("send photo taken success\n");
	}
	else
	{
		APP_CORE_ERROR("send photo taken fail!\n");
	}
}

static INT32 app_net_terminal_set_face_Info(int index, PFACE_INFO_T pInfo)
{
	if (index == -1 && pInfo != NULL)
	{
		if (check_same_driver_id((UINT8*)pInfo->identityID) == OK)
		{
			return ERROR;
		}
		
		MSG_Q_ID hande;

		if (sys_mqueue_create(&hande, "take_Photo", 2, sizeof(FACE_INFO_T)) != OK)
		{
			APP_CORE_ERROR("mqueue_create failed:%d\n ", ERROR);
			return ERROR;
		}

		if (sys_mqueue_send(&hande, (char *)pInfo, sizeof(FACE_INFO_T), WAIT_FOREVER))
		{
			APP_CORE_ERROR("send face msg failed!\n");
			return ERROR;
		}

		if (sys_pthread_create(NULL, "TERMINAL_TAKE_PHOTO", TASK_PRIORITY_4, SIZE_32KB, (FUNCPTR)take_photo, 1, hande) != 0)
		{
			APP_CORE_ERROR("create app_net_terminal_take_photo failed\n");
			return ERROR;
		}
	}
	else if (index != -1 && pInfo != NULL)
	{
		return set_face_info(index, pInfo);
	}
	else if (index != -1 && pInfo == NULL)
	{
		if (face_user_info_del(index) == ERROR)
		{
			APP_CORE_ERROR("net screen face_jpeg_reg,error!\n");
			return ERROR;
		}

		CHAR fileName[PATH_MAX_LEN] = {0};

		if (find_face_path(index, fileName, sizeof(fileName))== ERROR)
		{
			APP_CORE_ERROR("get face file path err !\n");
			return ERROR;
			
		}

		if (sys_file_exist(fileName) == OK)
		{
			sys_file_remove(fileName);
			APP_CORE_NOTE(" sys_file_remove %s\n", fileName);
			return OK;
		}
		else
		{
			APP_CORE_NOTE("Not Exit Path:%s\n", fileName);
			return ERROR;
		}
	}
	return ERROR;
}

static INT32 app_net_terminal_take_photo(int channel, int type)
{
	if (channel != 2 || type != 10)
	{
		return ERROR;
	}
	//if (sys_pthread_create(NULL, "TERMINAL_TAKE_PHOTO", TASK_PRIORITY_4, SIZE_32KB, (FUNCPTR)take_photo, 2, channel, type) != 0)
	//{
	//	APP_CORE_ERROR("create app_net_terminal_take_photo failed\n");
	//	return ERROR;
	//}
	return OK;
}


static INT32 app_net_terminal_get_peripheral_status(PPERI_STATUS_T pstPeriStatus)
{
	if (pstPeriStatus == NULL)
	{
		return ERROR;
	}
	
	pstPeriStatus->lift = app_veh_lift_status_get() == SENSOR_ABNORML ? 2 : 0;
	pstPeriStatus->carry = app_veh_cover_status_get() == SENSOR_ABNORML ? 2 : 0;
	pstPeriStatus->hermetic = app_veh_load_status_get() == LOAD_CONENCT_ABNORMAL ? 2 : 0;
	pstPeriStatus->led = app_led_connect_state_get() == FALSE ? 2 : 0;
	pstPeriStatus->audioAlarm = mcu_wanhang_alarm_sensor_connect_state_get() == FALSE ? 2 : 0;
	pstPeriStatus->conbox = app_can_box_connect_status_get() == FALSE ? 2 : 0;
	
	INT32 i;
	for (i = FIRST_CHAN_NO; i < NINTH_CHAN_NO; i++)
	{
		pstPeriStatus->cam[i - 1] = app_stream_conn_state_get(i) == FALSE ? 2 : 0;
	}

	return OK;
}

static VOID checking()
{
	char msg[sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2808;
	PCHECk_INFO_T pInfo = (PCHECk_INFO_T)(msg + sizeof(MSG_HDR_T));
	pInfo->checkCount = 6;

	/*举升传感器*/
	strncpy(pInfo->content, "举升传感器", sizeof(pInfo->content));
	pInfo->index = 0;
	pInfo->result = app_veh_lift_status_get() == SENSOR_ABNORML ? 2 : 0;
	if (!net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)))
	{
		return;
	}
	sleep(1);

	memset(pInfo->content, 0, sizeof(pInfo->content));
	strncpy(pInfo->content, "密闭传感器", sizeof(pInfo->content));
	pInfo->index++;
	pInfo->result = app_veh_cover_status_get() == SENSOR_ABNORML ? 2 : 0;
	if (!net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)))
	{
		return;
	}
	sleep(1);

	memset(pInfo->content, 0, sizeof(pInfo->content));
	strncpy(pInfo->content, "载重传感器", sizeof(pInfo->content));
	pInfo->index++;
	pInfo->result = app_led_connect_state_get() == LOAD_CONENCT_ABNORMAL ? 2 : 0;
	if (!net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)))
	{
		return;
	}
	sleep(1);

	memset(pInfo->content, 0, sizeof(pInfo->content));
	strncpy(pInfo->content, "LED屏幕", sizeof(pInfo->content));
	pInfo->index++;
	pInfo->result = app_led_connect_state_get() == FALSE ? 2 : 0;
	if (!net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)))
	{
		return;
	}
	sleep(1);

	memset(pInfo->content, 0, sizeof(pInfo->content));
	strncpy(pInfo->content, "声光报警器", sizeof(pInfo->content));
	pInfo->index++;
	pInfo->result = mcu_wanhang_alarm_sensor_connect_state_get() == FALSE ? 2 : 0;
	if (!net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)))
	{
		return;
	}
	sleep(1);

	memset(pInfo->content, 0, sizeof(pInfo->content));
	strncpy(pInfo->content, "can盒子", sizeof(pInfo->content));
	pInfo->index++;
	pInfo->result = app_can_box_connect_status_get() == FALSE ? 2 : 0;
	if (!net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CHECk_INFO_T)))
	{
		return;
	}
}

static INT32 app_net_terminal_checkSelf(VOID)
{
	if (sys_pthread_create(NULL, "TERMINAL_CHECK_SELF", TASK_PRIORITY_4, SIZE_32KB, (FUNCPTR)checking, 0) != 0)
	{
		APP_CORE_ERROR("create app_net_terminal_checkSelf failed\n");
		return ERROR;
	}

	return OK;
}

INT32 app_net_terminal_message_send(TERMINAL_MESSAGE_T* pstMsg)
{
	if (pstMsg == NULL || pstMsg->buf == NULL)
	{
		return ERROR;
	}

	if (pstMsg->len >= CONTENT_MAX_LEN)
	{
		APP_CORE_ERROR("message too long !\n");
		return ERROR;
	}

	char msg[sizeof(MSG_HDR_T) + sizeof(MESSAGE_INFO_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2802;

	PMESSAGE_INFO_T pMsg = (PMESSAGE_INFO_T)(msg + sizeof(MSG_HDR_T));
	pMsg->msgType = pstMsg->msgType;
	pMsg->showType = pstMsg->showType;
	pMsg->durction = pstMsg->durction;
	pMsg->priority = pstMsg->priority;
	strncpy(pMsg->message, pstMsg->buf, sizeof(pMsg->message) - 1);
	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(MESSAGE_INFO_T)))
	{
		APP_CORE_NOTE("send message success\n");
		return OK;
	}
	else
	{
		APP_CORE_ERROR("send message fail!\n");
		return ERROR;
	}
	return OK;
}

INT32 app_net_terminal_certify_send(UINT8 operate, JT808_ELE_WAYBILL_INFO_T *pstEleWay)
{
	if (pstEleWay == NULL)
	{
		return ERROR;
	}

	if (pstEleWay->uTextLen >= CERTIFY_MAX_LEN)
	{
		APP_CORE_ERROR("certify message too long !\n");
		return ERROR;
	}

	char msg[sizeof(MSG_HDR_T) + sizeof(CERITFY_T)] = {0};
	PMSG_HDR_T phdr = (PMSG_HDR_T)msg;
	phdr->msgID = 2803;

	PCERITFY_T pCeritfy = (PCERITFY_T)(msg + sizeof(MSG_HDR_T));
	pCeritfy->operate = operate;
	pCeritfy->type = pstEleWay->ucWayBlillType;
	pCeritfy->id = pstEleWay->uWayBillID;
	pCeritfy->startTime = pstEleWay->uStartTime;
	pCeritfy->endTime = pstEleWay->uEndTime;
	pCeritfy->len = pstEleWay->uTextLen;
	strncpy(pCeritfy->detail, (char*)pstEleWay->szContent, sizeof(pCeritfy->detail) - 1);

	if (net_terminal_notify(msg, sizeof(MSG_HDR_T) + sizeof(CERITFY_T)))
	{
		APP_CORE_NOTE("send certify success\n");
		return OK;
	}
	else
	{
		APP_CORE_ERROR("send certify fail!\n");
		return ERROR;
	}
	
}

static INT32 app_net_terminal_ceritfy_num(VOID)
{
	return lcd_sqlite_table_total_num_get(SQLITE_ELE_WAY_BILL_TABLE, 1);
}

static INT32 app_net_terminal_ceritfy_get(UINT32 id, PCERITFY_T pCeritfy)
{
	SQLITE_WAYBILL_MESSAGE_T stWayBill = {0};
	if (lcd_sqlite_way_bill_msg_request(LCD_SQLITE_CHECK_CONTENT, SQLITE_TABLE_MAX_NUM, id, &stWayBill) == ERROR)
	{
		APP_CORE_ERROR("query certify fail!\n");
		return ERROR;
	}

	/*内容赋值*/
	pCeritfy->id = stWayBill.uWayBillId;
	pCeritfy->startTime = stWayBill.uWBStartTime;
	pCeritfy->endTime = stWayBill.uWBEndTime;
	pCeritfy->type = stWayBill.ucWayBlillType;
	pCeritfy->len = stWayBill.uDataLen;
	strncpy(pCeritfy->detail, (char*)stWayBill.szData, sizeof(pCeritfy->detail) - 1);
	
	return OK;
}

static INT32 app_net_terminal_area_num(VOID)
{
	return ERROR;
}

static INT32 app_net_terminal_area_get(UINT32 id, PAREA_T pArea)
{
	return ERROR;
}

void app_net_terminal_area_set(UINT32 num, PAREA_T* pArea)
{

}

#endif //CONFIG_NET_TERMINAL

#endif
