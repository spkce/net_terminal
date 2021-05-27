#ifndef __NET_TERMINAL_H__
#define __NET_TERMINAL_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define NET_APP_DEV_INFO_LEN 16
#define NET_APP_VERSION_LEN 32
#define NET_APP_DATE_LEN 24      /*时间，时区字符串最大长度*/

/**
 * @brief 获取设备信息
 */

typedef struct tagDevInfo
{
    unsigned int uDDR;
    unsigned int uLanguage;
    char  sDeviceType[NET_APP_DEV_INFO_LEN];/*设备型号，AE-CN2213-C1*/
    char  sFirmVersion[NET_APP_DEV_INFO_LEN];/*固件版本，V1.1.0*/
    char  sFirmDate[NET_APP_DEV_INFO_LEN];/*固件日期，2016.04.15*/
    char  sParamVersion[NET_APP_DEV_INFO_LEN];/*参数版本，V1.2.0*/
    char  sSerialNum[NET_APP_DEV_INFO_LEN];/*序列号，585022848*/
    char  sVerifyCode[NET_APP_DEV_INFO_LEN];/*设备验证码，HNDAGK*/
    char  sCustomID[NET_APP_DEV_INFO_LEN];/*定制单号*/
    char  sHardwareVer[NET_APP_DEV_INFO_LEN];/*硬件版本，V1.1.0*/
    char  sMCUVer[NET_APP_VERSION_LEN];/*MCU版本号*/
    char  sDspVer[NET_APP_VERSION_LEN];/*DSP版本号*/
    char  sFpgaVer[NET_APP_VERSION_LEN];/*FPGA版本号*/
	char  sGpsVer[NET_APP_VERSION_LEN];/*GPS版本号*/
}DEV_INFO_T, *PDEV_INFO_T;

typedef struct tagDevStatus
{
	int accStatus;/*acc 状态*/
	int CSQ;/*GSM信号强度*/
	int locationStatus; /*定位状态*/
	int bizPIfLoginStatus; /*业务平台登录状态*/
	char  curTime[NET_APP_DATE_LEN];/*设备时间*/

}DEV_STATUS_T, *PDEV_STATUS_T;

typedef struct tagVehStatus
{
	int feedProtection; /*acc 状态*/
	int gear;/*挡位*/
 	int carryStatus;/*载货状态*/
	int hermeticStatus;/*密闭状态*/
	int liftStatus;/*举升状态*/
	int speedLimitStatus;/*限速状态*/
	int liftLimitStatus;/*限举状态*/
	int rotateLimitStatus;/*限转状态*/
	int lockStatus;/*锁车状态*/
	int maintainMode;/*维护模式*/
	int speedLimitThreshold;/*限速阈值*/
}VEH_STATUS_T, *PVEH_STATUS_T;

typedef struct tagSetting
{
	char sTime[NET_APP_DATE_LEN];/*时间，目前只支持时间的获取*/
}SETTING_T, *PSETTING_T;

typedef struct tagTouchInfo
{
	int touchX;/*X坐标*/
	int touchY;/*Y坐标*/
	int screenWidth;/*屏幕宽*/
	int screenHeight;/*屏幕高*/
	int touchType;/*触摸类型：0释放；1按下*/
}TOUCH_INFO_T, *PTOUCH_INFO_T;


/*外部接口函数*/
typedef struct tagAdapterFunc
{
	int (*device_info_get)(PDEV_INFO_T pstDevInfo);
	int (*device_status_get)(PDEV_STATUS_T pstDevStatus);
	int (*vehicle_status_get)(PVEH_STATUS_T pstVehStatus);
	int (*setting_get)(PSETTING_T pstSetting);
	int (*send_touch_info)(PTOUCH_INFO_T pstSetting);
}ADAPTER_T, *PADAPTER_T;



void net_termianl_init();

PADAPTER_T net_terminal_adapter_get();


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
