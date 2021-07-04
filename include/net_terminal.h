#ifndef __NET_TERMINAL_H__
#define __NET_TERMINAL_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define NET_APP_DEV_INFO_LEN 16
#define NET_APP_VERSION_LEN 32
#define NET_APP_DATE_LEN 24      /*时间，时区字符串最大长度*/
#define FACE_NAME_LEN 20
#define FACE_IDENTITY_LEN 32
#define FACE_LICENSE_LEN 32
#define CONTENT_MAX_LEN 64
#define PATH_MAX_LEN 128           /*路径最大长度*/
#define CAM_MAX 8

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
	char curTime[NET_APP_DATE_LEN];/*设备时间*/

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

typedef struct tagPeriStatus
{
	int lift;/*举升传感器状态*/
	int carry;/*密闭传感器状态*/
	int hermetic;/*载重传感器状态*/
	int led;/*LED屏状态*/
	int audioAlarm;/*声光报警器状态*/
	int conbox;/*can盒子状态*/
	int cam[CAM_MAX];/*摄像头状态*/
}PERI_STATUS_T, *PPERI_STATUS_T;

typedef struct tagCarStatus
{
	int corneringLamp;	/*转向灯 状态*/
	int brake;			/*刹车 状态*/
}CAR_STA_T, *PCAR_STA_T;

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

typedef struct tagMsghdr
{
	unsigned int msgID;
}MSG_HDR_T, *PMSG_HDR_T;

typedef struct tagWarnInfo
{
	int type;
}WARN_INFO_T, *PWARN_INFO_T;

typedef struct tagFaceInfo
{
	int faceID;
	char name[FACE_NAME_LEN];
	char identityID[FACE_IDENTITY_LEN];
	char path[PATH_MAX_LEN];
	char license[FACE_LICENSE_LEN];
}FACE_INFO_T, *PFACE_INFO_T;

typedef struct tagADASAlarm
{
	int detailType;
	int channel;
	int result;
	char picName[PATH_MAX_LEN];
	char vIdeoName[PATH_MAX_LEN];
	
}ADAS_INFO_T,PADAS_INFO_T;
typedef struct tagPhotoTaken
{
	int type;
	int channel;
	int filesize;
	int result;
	char path[PATH_MAX_LEN];
	char thmPath[PATH_MAX_LEN];
	char startTime[NET_APP_DATE_LEN];
}PHOTO_TAKEN_T,PPHOTO_TAKEN_T;

typedef struct tagNotification
{
	char type[32];
	union {
		ADAS_INFO_T adasAlarm;
		PHOTO_TAKEN_T photoTaken;
	};
}NOTIFICATION_T, *PNOTIFICATION_T;

typedef struct tagMsgInfo
{
	int msgType;
	int showType;
	int durction;
	int priority;
	char message[CONTENT_MAX_LEN];
}MESSAGE_INFO_T, *PMESSAGE_INFO_T;

typedef struct tagcheckSelfInfo
{
	int checkCount;
	int index;
	int result;
	char content[CONTENT_MAX_LEN];
}CHECk_INFO_T, *PCHECk_INFO_T;

/*外部接口函数*/
typedef struct tagAdapterFunc
{
	int (*device_info_get)(PDEV_INFO_T pstDevInfo);
	int (*device_status_get)(PDEV_STATUS_T pstDevStatus);
	int (*vehicle_status_get)(PVEH_STATUS_T pstVehStatus);
	int (*peripheral_status_get)(PPERI_STATUS_T pstPeriStatus);
	int (*car_status_get)(PCAR_STA_T pstSetting);
	int (*setting_get)(PSETTING_T pstSetting);
	int (*send_touch_info)(PTOUCH_INFO_T pstSetting);
	int (*get_face_total_number)(void);
	int (*get_face_info)(unsigned int index, PFACE_INFO_T pInfo);
	int (*set_face_info)(int index, PFACE_INFO_T pInfo);
	int (*take_photo)(int channel, int type);
	int (*checkSelf)(void);
}ADAPTER_T, *PADAPTER_T;


/**
 * @brief 初始化安卓屏
 */
void net_termianl_init();

/**
 * @brief 获取适配器指针
 * @return 适配器指针
 */
PADAPTER_T net_terminal_adapter_get();

/**
 * @brief 消息推送
 * @param buf 消息缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_notify(char* buf, int len);

/**
 * @brief GPS数据推送
 * @param buf GPS数据缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_pushGPS(char* buf, int len);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
