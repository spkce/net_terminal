#ifndef __ORDER_H__
#define __ORDER_H__

#include "jsoncpp.h"
namespace Screen
{

class IOrder
{
public:
	enum
	{
		/*系统类命令*/
		AE_GET_ALL_CURRENT_SETTINGS = 1, /*获取所有设置的当前参数*/
		AE_GET_BATTERY_LEVEL = 2,		 /*获取电池状态*/
		AE_GET_CAMERAS_STATUS = 3,		 /*获取所有通道接入和录像状态*/
		AE_GET_GSENSOR_DATA = 4,		 /*获取设备G-sensor数据*/
		AE_GET_GPS = 5,					 /*获取当前GPS坐标*/
		AE_GET_DEVICE_INFO = 6,			 /*获取设备信息*/
		AE_GET_VEHICLE_INFO = 8,		 /*获取车辆相关信息*/
		AE_SET_VEHICLE_INFO = 9,		 /*设置车辆相关信息*/
		AE_GET_DRIVER_INFO = 10,		 /*获取驾驶员相关信息*/
		AE_SET_DRIVER_INFO = 11,		 /*设置驾驶员相关信息*/

		AE_GET_SATELLITE_INFO = 19, /*获取设备当前的搜星信息*/

		AE_GET_DEVICE_STATUS = 26, /*获取设备状态*/
		AE_GET_VEHICLE_STATUS = 27, /*获取车辆状态*/

		AE_GET_PICTURE_SETTING = 186,  /*获取图像设置*/
		AE_SET_PICTURE_SETTING = 187,  /*设置图像设置*/
		AE_GET_COMPRESS_SETTING = 188, /*获取压缩设置*/
		AE_SET_COMPRESS_SETTING = 189, /*设置压缩设置*/

		AE_GET_IMAGE_SETTING = 190,	  /*获取图片设置*/
		AE_SET_IMAGE_SETTING = 191,	  /*设置图片设置*/
		AE_GET_GENERIC_SETTING = 192, /*获取通用设置*/
		AE_SET_GENERIC_SETTING = 193, /*设置通用设置*/
		AE_GET_PROMPT_SETTING = 194,  /*获取提醒设置*/
		AE_SET_PROMPT_SETTING = 195,  /*设置提醒设置*/
		AE_GET_ALERT_SETTING = 196,	  /*获取告警设置*/
		AE_SET_ALERT_SETTING = 197,	  /*设置告警设置*/
		AE_GET_SENSOR_SETTING = 198,  /*获取传感设置*/
		AE_SET_SENSOR_SETTING = 199,  /*设置传感设置*/

		/*媒体命令*/
		AE_RECORD_START = 201,		 /*开启录像*/
		AE_RECORD_STOP = 202,		 /*关闭录像*/
		AE_EVENT_RECORD_START = 203, /*开启紧急录像*/
		AE_AUDIO_RECORD_START = 204, /*开启音频录像*/
		AE_AUDIO_RECORD_STOP = 205,	 /*关闭音频录像*/

		/*网络接口类命令*/
		AE_WIFI_RESTART = 301,		  /*启动wifi*/
		AE_GET_STA_PARAM = 302,		  /*获取STA参数*/
		AE_SET_STA_PARAM = 303,		  /*设置STA参数*/
		AE_GET_AP_PARAM = 304,		  /*获取AP参数*/
		AE_SET_AP_PARAM = 305,		  /*设置AP参数*/
		AE_GET_4G_PARAM = 306,		  /*获取4G参数*/
		AE_SET_4G_PARAM = 307,		  /*设置4G参数*/
		AE_GET_NETWORK_SETTING = 398, /*获取网络设置*/
		AE_SET_NETWORK_SETTING = 399, /*设置网络设置*/

		/*存储类命令*/
		AE_GET_SD_LETTER = 401,			/*获取已插入盘符*/
		AE_GET_SD_INFO = 402,			/*获取SD信息*/
		AE_SET_SD_LOCK_STATUS = 403,	/*设置SD锁状态*/
		AE_SET_SD_PASSWD = 404,			/*设置SD密码*/
		AE_FORMAT = 405,				/*格式化SD卡*/
		AE_GET_RECORD_SCHEDILE = 406,	/*获取录像计划*/
		AE_SET_RECORD_SCHEDILE = 407,	/*设置录像计划*/
		AE_COPY_DAY_SCHEDILE = 408,		/*复制一天的录像计划*/
		AE_COPY_CHANNEL_SCHEDILE = 409, /*复制一个通道的录像计划*/
		AE_EXPORT_MEDIA_FILE = 410,		/*设备媒体文件导出到外部存储设备*/
		AE_EXPORT_LOG = 411,			/*设备日志导出到外部存储设备*/
		AE_EXPORT_CONFIG = 414,			/*将设备中的配置文件导入到外部设备*/
		AE_IMPORT_CONFIG = 415,			/*将外部设备中的配置文件导入到设备*/
		AE_CONCEL_EXPORT = 416,			/*取消文件导出*/
		AE_GET_STORAGE_SETTING = 498,	/*获取存储设置*/
		AE_SET_STORAGE_SETTING = 499,	/*设置存储设置*/
		/*时间类命令*/
		AE_GET_DAYLIGHT_TIME = 501, /*获取夏令时*/
		AE_SET_DAYLIGHT_TIME = 502, /*设置夏令时*/
		AE_GET_TIMEZONE = 503,		/*获取时区*/
		AE_SET_TIMEZONE = 504,		/*设置时区*/
		AE_GET_TIME_SETTING = 598,	/*获取时间设置*/
		AE_SET_TIME_SETTING = 599,	/*设置时间设置*/

		/*通知类命令*/
		AE_NOTIFICATION = 601, /*通知类消息*/

		/*平台连接类命令*/
		AE_GET_PLATFORM_CONN_INFO = 701,	/*获取平台信息*/
		AE_SET_PLATFORM_CONN_INFO = 702,	/*设置平台信息*/
		AE_GET_808_CONN_INFO = 703,			/*获取808参数信息*/
		AE_SET_808_CONN_INFO = 704,			/*设置808参数信息*/
		AE_GET_808_CONN_INFO_2 = 705,		/*获取808_2参数信息*/
		AE_SET_808_CONN_INFO_2 = 706,		/*设置808_2参数信息*/
		AE_GET_OPERATE_PLATFORM_INFO = 707, /*获取运维平台参数信息*/
		AE_SET_OPERATE_PLATFORM_INFO = 708, /*设置运维平台参数信息*/
		AE_GET_NTP_PLATFORM_INFO = 709,		/*获取NTP平台参数信息*/
		AE_SET_NTP_PLATFORM_INFO = 710,		/*设置NTP平台参数信息*/

		/*人脸命令*/
		AE_GET_FACE_INFO = 922,				   /*获取设备存储的人脸信息*/
		AE_SET_FACE_INFO = 923,				   /*设置设备存储的人脸信息*/
		AE_GET_OVERTIME_DRIVING_SETTING = 924, /*用于获取长时间驾驶时间段参数*/
		AE_SET_OVERTIME_DRIVING_SETTING = 925, /*用于设置长时间驾驶时间段参数*/
		AE_FACE_CONTRAST = 932,					/*人脸比对结果*/

		/*IPC配置*/
		AE_GET_ADDED_IPC_LIST = 1001,	/*获取已经添加的ipc列表*/
		AE_GET_ADDABLE_IPC_LIST = 1002, /*获取在线的ipc列表*/
		AE_ADD_IPC = 1003,				/*快速添加IPC*/
		AE_DEL_IPC = 1004,				/*删除IPC*/
		AE_GET_PERIPHERAL_STATUS = 1008, /*获取外设状态*/

		/*设备能力集大类*/
		AE_CAPABILITY_GET = 1901,			   /*获取能力集大类*/
		AE_CAPABILITY_IMAGE_GET = 1911,		   /*获取图像能力集*/
		AE_CAPABILITY_BASIC_GET = 1921,		   /*获取基础能力集*/
		AE_CAPABILITY_NETWORK_GET = 1931,	   /*获取网络能力集*/
		AE_CAPABILITY_STORAGE_GET = 1941,	   /*获取存储能力集*/
		AE_CAPABILITY_INTELLIGENCE_GET = 1951, /*获取智能驾驶能力集大类*/
		AE_CAPABILITY_PROMPT_GET = 1952,	   /*获取提醒能力集*/
		AE_CAPABILITY_ALERT_GET = 1953,		   /*获取告警能力集*/
		AE_CAPABILITY_SENSOR_GET = 1954,	   /*获取传感能力集*/
		AE_CAPABILITY_ADAS_GET = 1955,		   /*获取ADAS能力集*/
		AE_CAPABILITY_DBA_GET = 1956,		   /*获取DBA能力集*/
		AE_CAPABILITY_VSD_GET = 1957,		   /*获取VSD能力集, 已弃用，能力集归于DBA*/
		AE_CAPABILITY_BSD_GET = 1958,		   /*获取BSD能力集*/

		AE_CAPABILITY_FACE_GET = 1959, /*获取人脸识别能力集*/

		AE_CAPABILITY_TIME_GET = 1961, /*获取时间能力集*/

		AE_CAPABILITY_WHD_GET = 1962, /*获取WHD能力集*/

		AE_CAPABILITY_PICTURE_GET = 1971,	/*获取图片能力集*/
		AE_CAPABILITY_COMPRESS_GET = 1981,	/*获取压缩能力集*/
		AE_CAPABILITY_BLUETOOTH_GET = 1991, /*获取蓝牙能力集*/
		AE_CAPABILITY_IPC_GET = 1993,		/*ipc能力集*/

		/*智能类命令*/
		AE_GET_ADAS_SETTING = 901,			   /*获取ADAS设置*/
		AE_SET_ADAS_SETTING = 902,			   /*设置ADAS设置*/
		AE_GET_ADAS_CALIBRATION = 903,		   /*获取ADAS标定*/
		AE_SET_ADAS_CALIBRATION = 904,		   /*设置ADAS标定*/
		AE_GET_DBA_SETTING = 905,			   /*获取DBA设置*/
		AE_SET_DBA_SETTING = 906,			   /*设置DBA设置*/
		AE_ENTER_SPEED_CALIBRATION = 907,	   /*进入速度标定*/
		AE_EXIT_SPEED_CALIBRATION = 908,	   /*离开速度标定*/
		AE_START_SPEED_CALIBRATION = 909,	   /*开始速度标定*/
		AE_GET_SPEED_CALIBRATION_STATUS = 910, /*获取速度标定状态*/
		AE_GET_CAR_STATUS = 911,			   /*获取车辆状态*/
		AE_GET_VSD_SETTING = 912,			   /*获取VSD设置*/
		AE_SET_VSD_SETTING = 913,			   /*设置VSD设置*/
		AE_START_ADAS_CALIBRATION = 914,	   /*开始ADAS相机标定*/
		AE_GET_SPEED_CALIBRATION = 915,		   /*获取速度标定*/
		AE_SET_SPEED_CALIBRATION = 916,		   /*设置速度标定*/
		AE_TURN_CALIBRATION = 917,			   /*转弯标定*/
		AE_BREAK_CALIBRATION = 918,			   /*刹车标定*/
		AE_GET_SPEED = 919,					   /*获取车速*/
		AE_GET_BSD_SETTING = 920,			   /*获取BSD设置*/
		AE_SET_BSD_SETTING = 921,			   /*设置BSD设置*/
		AE_GET_IO_WARN_INFO = 928,			   /*获取IO报警设置*/
		AE_SET_IO_WARN_INFO = 929,			   /*设置IO报警通道设置*/
		AE_GET_PULSE_SETTING = 930,			   /*获取脉冲设置*/
		AE_SET_PULSE_SETTING = 931,			   /*设置脉冲参数*/
		AE_GET_IO_OUTPUT_SETTING = 934,		   /*获取IO报警输出*/
		AE_SET_IO_OUTPUT_SETTING = 935,		   /*设置IO报警输出*/

		AE_GET_WHD_SETTING = 938, /*获取WHD设置*/
		AE_SET_WHD_SETTING = 939, /*设置WHD设置*/
		AE_SET_PFS_INFO = 940,	  /*获取实时客流信息*/

		AE_GET_CUSTOM_SMART_CHAN_INFO = 941, /*获取用户自定义智能摄像头信息*/
		AE_SET_CUSTOM_SMART_CHAN_INFO = 942, /*设置用户自定义智能摄像头信息*/

		/* 事件关联类 */
		AE_GET_EVENT_DISPLAY_SETTING = 950, /* 获取事件显示 */
		AE_SET_EVENT_DISPLAY_SETTING = 951,
		/*过程控制类命令*/
		AE_START_SESSION = 257,       /*握手*/
		AE_STOP_SESSION = 258,       /*断开*/
		/*系统类命令*/
		AE_CHECK_SELF = 2200,	 /*自检请求*/
		AE_RESET_DEFAULT = 2201,	 /*恢复默认参数*/
		AE_REBOOT_SYSTEM = 2202,	 /*重启系统*/
		AE_SHUTDOWN_SYSTEM = 2203,	 /*关机*/
		AE_UPGRADE = 2204,			 /*升级*/
		AE_GET_SETTING = 2205,		 /*获取某项设置的当前参数*/
		AE_SET_SETTING = 2206,		 /*配置某项设置的当前参数*/
		AE_GET_UPGRADE_PATH = 2207,	 /*获取升级路径*/
		AE_GET_ACTIVE_STATUS = 2208, /*获取设备激活状态*/
		AE_GET_CHANNEL_INFO = 2209,	 /*获取OSD通道信息*/
		AE_SET_CHANNEL_INFO = 2210,	 /*设置OSD通道信息*/
		AE_APK_UPGRADE = 2211,		 /*卡升级安卓*/
		AE_STARTUP_SYSTEM = 2212,	 /*开机命令*/
		AE_DOWNLOAD = 2213,			 /*下载*/
		AE_GET_LICENSE_INFO = 2219,	/*获取许可证消息*/
		AE_START_SELF_CHECKING = 2220,	/*设备启动自检*/
		AE_GET_AREA_INFO = 2221,	/*获取电子围栏信息*/

		/*文件类命令*/
		AE_GET_VIDEO_FILE_LIST = 2301,		   /*获取录像文件列表*/
		AE_GET_IMAGE_FILE_LIST = 2302,		   /*获取图像文件列表*/
		AE_GET_AUDIO_FILE_LIST = 2303,		   /*获取音频文件列表*/
		AE_DELETE_FILE = 2304,				   /*删除文件*/
		AE_GET_TOTAL_NUM = 2305,			   /*获取总文件数目*/
		AE_GET_RECORD_STATUS_BY_MONTH = 2306,  /*获取当月每天的录像状态*/
		AE_LOCK_FILE = 2307,				   /*文件加锁*/
		AE_UNLOCK_FILE = 2308,				   /*文件解锁*/
		AE_GET_VIDEO_TIMETAMP = 2309,		   /*获取录像开始时间点及结束时间点*/
		AE_GET_VIDEO_FILE_LIST_BY_TIME = 2310, /*获取某一天的录像时间段*/
		AE_GET_RECORD_DAYS = 2311,			   /*获取当前设备所有录像的日期*/

		/*透传类命令*/
		AE_GET_CUSTOM = 2401, /*获取自定义命令*/ 
		AE_SET_CUSTOM = 2402, /*设置自定义命令*/

		/*媒体类命令*/
		AE_START_PREVIEW = 2501,		  /*开始预览*/
		AE_STOP_PREVIEW = 2502,			  /*停止预览*/
		AE_START_PLAYBACK = 2503,		  /*开始回放*/
		AE_STOP_PLAYBACK = 2504,		  /*停止回放*/
		AE_START_AUDIO = 2505,			  /*开始音频回放*/
		AE_STOP_AUDIO = 2506,			  /*停止音频回放*/
		AE_TAKE_PHOTO = 2507,			  /*抓图*/
		AE_SET_RECORD_LOCK_STATUS = 2508, /*设置录像锁定状态*/
		AE_GET_RTSP_INFO = 2509,		  /*获取RTSP用户名和密码*/

		/*信息类参数*/
		AE_SEND_APP_INFO = 2704,		  /*app向设备发送信息*/
		AE_SEND_TOUCH_INFO = 2705,		/*app向设备发送触碰信息*/
		AE_SEND_UI_STATUS = 2706,		/*app向设备发送界面状态*/

		AE_SEND_AREA_INFO = 2804,		/*设备向app发送区域信息*/
		AE_CLEAR_ALL_AREA_INFO = 2805,	/*设备向app发送清空围栏指令*/
		AE_GET_APP_INFO = 2806,		/*设备向app查询版本信息*/
		AE_SEND_WARN_INFO = 2807,		/*设备向app发送BSD报警信息*/
		AE_SEND_SELF_CHECKING_INFO = 2808,		/*设备向app发送自检信息*/
		AE_SEND_PARAMETER = 2809,		/*设备向app发送参数*/


		AE_CAPABILITY_CALIBRATION_GET = 4101, /*获取标定能力*/

		/*工厂测试*/
		AE_FACTORY = 5001, /*工厂测试*/
	};

	enum
	{
		/*系统类错误码*/
		AE_SYS_NOERROR                          = 0,         /*正常*/
		AE_SYS_UNKNOWN_ERROR                    = 1,         /*操作异常，无法判定原因*/
		AE_SYS_SESSION_START_FAIL               = 2,         /*建立连接失败*/
		AE_SYS_INVALID_TOKEN                    = 3,         /*token错误*/
		AE_SYS_REACH_MAX_CLINT                  = 4,         /*客户端连接数达到上限*/
		AE_SYS_HDMI_INSERTED                    = 5,         /*APP请求建立连接时，HDMI端口有连接其他外设*/
		AE_SYS_NO_MORE_MEMORY                   = 6,         /*设备内存耗尽*/
		AE_SYS_PIV_NOT_ALLOWED                  = 7,         /*当前分辨率和帧率不支持在录像的时候抓拍图片*/
		AE_SYS_SYSTEM_BUSY                      = 8,         /*系统繁忙，无法处理当前请求*/
		AE_SYS_NOT_READY                        = 9,         /*设备初始化未完成*/
		AE_SYS_RESET_FAILED                     = 10,        /*设备复位失败*/
		AE_SYS_GET_FILE_LIST_FAILED             = 11,        /*获取文件列表失败*/
		AE_SYS_UNACTIVED                        = 12,        /*设备未激活*/
		AE_SYS_DEMO_MODE                        = 13,        /*设备处在演示模式，无法设置参数*/
		AE_NO_BATTERY                           = 14,        /*设备未装载电池*/
		AE_NO_TRAIN_INFO                        = 15,        /*未连接外部设备*/
	};

	/*协议类错误码*/
	enum
	{
		AE_PROT_JSON_PACKAGE_ERROR              =301,       /*json字符串不支持嵌套*/
		AE_PROT_JSON_PACKAGE_TIMEOUT            =302,       /*5秒内未收到json结束标志*/
		AE_PROT_JSON_SYNTAX_ERROR               =303,       /*json字符串的键值对包含语法错误*/
		AE_PROT_INVALID_OPTION_VALUE            =304,       /*AE_SET_SETTING命令的json字符串中包含不支持的选项*/
		AE_PROT_INVALID_OPERATION               =305,       /*不支持的命令号*/
		AE_PROT_INVALID_TYPE                    =306,       /*协议命令的type非法*/
		AE_PROT_INVALID_PARAM                   =307,       /*协议命令的param非法*/
		AE_PROT_INVALID_PATH                    =308,       /*请求的文件或目录不存在*/
		AE_TIMEZONE_INTERVAL_ERROR              =309,       /*夏令时间隔小于30天*/
		AE_TIMEZONE_WEEK_ERROR                  =310,       /*夏令时星期错误*/
		AE_TIMEZONE_DAY_ERROR                   =311,       /*夏令时日期错误*/
		AE_VOLTAGE_ERROR						=312,		/*设置失败，当前电压小于设置电压*/
		AE_VOLTAGE_NOT_CONNECTED				=313,		/*设置失败，未连接降压线*/
		AE_SET_VALUE_TOO_LOW				    =314,		/*设置参数过低*/
		AE_SET_VALUE_TOO_HIGH				    =314,		/*设置参数过高*/
	};
	/**
	* @brief 消息分发
	* @param msgID 消息ID
	* @param request 请求报文
	* @param response 回复
	* @return 成功/失败
	**/
	static bool orderHub(unsigned int msgID, Json::Value &request, Json::Value &response);
	/**
	* @brief 通知消息封装
	* @param msgID 消息ID
	* @param buf 消息内容
	* @param len 消息长度
	* @return 成功/失败
	**/
	static bool notifyHub(unsigned int msgID, char* buf, int len, Json::Value &send);
protected:
	/**
	* @brief 析构函数，设定protected权限，不可实例，可继承
	**/
	virtual ~IOrder() {};
};

}//Screen

#endif //__ORDER_H__
