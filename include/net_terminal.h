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
#define CERTIFY_MAX_LEN 256
#define MAX_POLYGON_VERTEX_NUM 30		/*最大多边形顶点数目*/
#define MAX_INFLECTION_POINT_NUM 50		/*最大拐点数目*/
#define MAX_AREA_NUM 50					/*最大区域数目*/
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
	int faceID;							/*人脸ID*/
	char name[FACE_NAME_LEN];			/*姓名*/
	char identityID[FACE_IDENTITY_LEN];	/*身份证*/
	char path[PATH_MAX_LEN];			/*人脸路径*/
	char license[FACE_LICENSE_LEN];		/*许可证号*/
}FACE_INFO_T, *PFACE_INFO_T;

typedef struct tagAlarm
{
	int detailType;
	int channel;
	char stime[NET_APP_DATE_LEN];
	char picName[PATH_MAX_LEN];
	char videoName[PATH_MAX_LEN];
}ALARM_INFO_T,*PALARM_INFO_T;

typedef struct tagPeriheralState
{
	int state;
	char deviceName[CONTENT_MAX_LEN];
}PERI_STATE_T, *PPERI_STATE_T;

typedef struct tagVehicleNotify
{
	int state;
}VEHICLE_NOTIFY_T, *PVEHICLE_NOTIFY_T;

typedef struct tagPhotoTaken
{
	int type;
	int channel;
	int filesize;
	int result;
	char path[PATH_MAX_LEN];
	char thmPath[PATH_MAX_LEN];
	char startTime[NET_APP_DATE_LEN];
}PHOTO_TAKEN_T, *PPHOTO_TAKEN_T;

typedef struct tagfaceContrast
{
	int result;
	unsigned int similarity;
}FACE_CONTRAST_T, *PFACE_CONTRAST_T;

typedef struct tagUpgradeReq
{
	char* url;
}UPGRADE_REQ_T, *PUPGRADE_REQ_T;

typedef struct tagGear
{
	unsigned int gear;
}GEAR_T, *PGEAR_T;

typedef struct tagNotification
{
	char type[32];
	union {
		ALARM_INFO_T alarm;
		PERI_STATE_T peripheral;
		VEHICLE_NOTIFY_T vehicle;
		PHOTO_TAKEN_T photoTaken;
		FACE_CONTRAST_T faceResult;
		UPGRADE_REQ_T upgrade;
		GEAR_T gear;
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

typedef struct tagCertify
{
	unsigned int operate;
	unsigned int id;
	unsigned int type;
	unsigned int startTime;
	unsigned int endTime;
	unsigned int len;
	char detail[CERTIFY_MAX_LEN];
}CERITFY_T, *PCERITFY_T;

typedef struct tagGpsPoint
{
	unsigned int latitude; 			/* 纬度*/
	unsigned int longtitude;		/*经度*/
}GPS_POINT, *PGPS_POINT;

typedef struct tagCircleArea
{
	unsigned int radius;
	GPS_POINT center;			/*中心点*/
}CIRCLE_AREA_T, *PCIRCLE_AREA_T;

typedef struct tagRectArea
{
	GPS_POINT leftPoint;		/*左上点*/
	GPS_POINT rightPoint;	/*右下点*/
}RECT_AREA_T, *PRECT_AREA_T;

typedef struct tagPolygonArea
{
	GPS_POINT vertex[MAX_POLYGON_VERTEX_NUM];
	unsigned int num;
}POLYGON_AREA_T, *PPOLYGON_AREA_T;

typedef struct tagRouteArea
{
	GPS_POINT inflctPoint[MAX_INFLECTION_POINT_NUM];
	unsigned int width[MAX_INFLECTION_POINT_NUM];
	unsigned int num;
}ROUTE_AREA_T, *PROUTE_AREA_T;

typedef struct tagArea
{
#define radius circle.radius
#define center circle.center
#define leftPoint rect.leftPoint
#define rightPoint rect.rightPoint
#define vertex polygon.vertex
#define vertexNum polygon.num
#define inflctPoint line.inflctPoint
#define lineWidth line.width
#define pointNum line.num

	union {
		CIRCLE_AREA_T circle;
		RECT_AREA_T rect;
		POLYGON_AREA_T polygon;
		ROUTE_AREA_T line;
	};
	unsigned int id;			/*区域ID*/
	unsigned int property;		/*区域属性*/
	unsigned int type;			/*区域类型*/
	
	char startTime[NET_APP_DATE_LEN];
	char endTime[NET_APP_DATE_LEN];
}AREA_T, *PAREA_T;

typedef struct tagAreaInfo
{
	int operate;		/*操作*/
	unsigned int areaNum; /*区域数量*/
	AREA_T area[MAX_AREA_NUM];
}AREA_INFO_T, *PAREA_INFO_T;

typedef struct tagFileCriteria
{
	int type;	/*录像类型。0-普通录像，1-紧急录像，2-手动录像(平台下发)，3-告警录像，9-全部录像(包括0,1,2,3)*/
	int channel;/*通道号，从0开始*/
	char startTime[NET_APP_DATE_LEN];
	char stopTime[NET_APP_DATE_LEN];
}FILE_CRITERIA_T, *PFILE_CRITERIA_T;

typedef struct tagFileInfo
{
	int lockState;
	unsigned int duration;
	unsigned int size;
	unsigned char type;
	char name[CONTENT_MAX_LEN];
	char startTime[NET_APP_DATE_LEN];
	
}FILE_INFO_T, *PFILE_INFO_T;

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
	int (*get_face_info)(int index, PFACE_INFO_T pInfo);
	int (*set_face_info)(int index, PFACE_INFO_T pInfo);
	int (*faceContrast)(const char* pic);
	int (*take_photo)(int channel, int type);
	int (*checkSelf)(void);
	int (*get_ceritfy_Num)(void);
	int (*get_ceritfy)(unsigned int id, PCERITFY_T pCeritfy);
	int (*get_area_Num)(void);
	int (*get_area)(unsigned int id, PAREA_T pArea);
	int (*upgrade_result)(unsigned int result, unsigned int progress);
	void* (*file_list_get)(unsigned int type, PFILE_CRITERIA_T pCriteria, unsigned int* num);
	int (*search_file_next)(int reverse, void *h, PFILE_INFO_T pFileInfo);
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
 * @brief 获取安卓屏连接状态
 * @return 在线：true；离线：false
 */
int net_termianl_is_inline();

/**
 * @brief 获取适配器指针
 * @param mod 模块名字
 * @param level 等级 4:关闭，3:所有等级 2:trace及以上 1:warning及以上 0:error
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_debug_set(const char* mod, int level);

/**
 * @brief 获取版本信息
 * @param buf 缓冲区 
 * @param len 消息缓长度
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_get_version(char* buf, unsigned int len);

/**
 * @brief 升级包是否合法
 * @param url 升级包路径 
 * @return 成功：返回true；失败：返回false
 */
int net_terminal_upgrade_check(const char* url);

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

/**
 * @brief 人脸对比结果发送
 * @param result 对比结果
 * @param similarity 相似度
 * @return 成功：返回true；失败：返回false
 */
void net_terminal_face_contrast_result(int result, unsigned int similarity);

/**
 * @brief 设置圆形电子围栏
 * @param operate :操作
 * @param p :电子围栏信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_circle_area_set(int operate, void* p);

/**
 * @brief 设置矩形电子围栏
 * @param operate :操作
 * @param p :电子围栏信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_rect_area_set(int operate, void* p);

/**
 * @brief 设置多边形电子围栏
 * @param operate :操作
 * @param p :电子围栏信息
 * @return 成功，返回true；失败，返回Efalse
 */
int net_terminal_polygon_area_set(int operate, void* p);

/**
 * @brief 设置路线
 * @param operate :操作
 * @param p :路线信息
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_line_area_set(int operate, void* p);

/**
 * @brief 删除电子围栏
 * @param type :电子围栏属性
 * @param total :删除总数
 * @param pId :删除ID列表
 * @return 成功，返回true；失败，返回false
 */
int net_terminal_area_delete(int type, unsigned int total, unsigned int * pId);


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
