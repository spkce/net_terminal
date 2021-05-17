
#include "IProtocl.h"
#include "jsoncpp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include "openssl/evp.h"
#include "aes_encrypt.h"
#include "rsa_app.h"
#include "Session.h"
#include "NetProtocl.h"
#include "terminal.h"
#include <arpa/inet.h>

using namespace NetServer;
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

		/*IPC配置*/
		AE_GET_ADDED_IPC_LIST = 1001,	/*获取已经添加的ipc列表*/
		AE_GET_ADDABLE_IPC_LIST = 1002, /*获取在线的ipc列表*/
		AE_ADD_IPC = 1003,				/*快速添加IPC*/
		AE_DEL_IPC = 1004,				/*删除IPC*/

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

		AE_SEND_APP_INFO = 2704,		  /*app向设备发送信息*/
		AE_SEND_TOUCH_INFO = 2705,		/*app向设备发送触碰信息*/
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
	static bool orderHub(unsigned int msgID, Json::Value &request, Json::Value &response);
protected:
	virtual ~IOrder() {};
};

class COrderSysterm : public IOrder
{
public:
	virtual ~COrderSysterm() {};

	static int getDeviceSetting(Json::Value &request, Json::Value &response);
	static int getBatteryLevel(Json::Value &request, Json::Value &response);
	static int getCameraStatus(Json::Value &request, Json::Value &response);
	static int getGSensorData(Json::Value &request, Json::Value &response);
	static int getGPSData(Json::Value &request, Json::Value &response);
	static int getDeviceInfo(Json::Value &request, Json::Value &response);
	static int getVehicleInfo(Json::Value &request, Json::Value &response);
	static int setVehicleInfo(Json::Value &request, Json::Value &response);
	static int getDriverInfo(Json::Value &request, Json::Value &response);
	static int setDriverInfo(Json::Value &request, Json::Value &response);
	static int getSatelliteInfo(Json::Value &request, Json::Value &response);
	static int getDeviceStatus(Json::Value &request, Json::Value &response);
	static int getVehicleStatus(Json::Value &request, Json::Value &response);
	static int getPictureSetting(Json::Value &request, Json::Value &response);
	static int setPictureSetting(Json::Value &request, Json::Value &response);
	static int getCompressSetting(Json::Value &request, Json::Value &response);
	static int setCompressSetting(Json::Value &request, Json::Value &response);
	static int getImageSetting(Json::Value &request, Json::Value &response);
	static int setImageSetting(Json::Value &request, Json::Value &response);
	static int getGenericSetting(Json::Value &request, Json::Value &response);
	static int setGenericSetting(Json::Value &request, Json::Value &response);
	static int getPromptSetting(Json::Value &request, Json::Value &response);
	static int setPromptSetting(Json::Value &request, Json::Value &response);
	static int getAlertSetting(Json::Value &request, Json::Value &response);
	static int setAlertSetting(Json::Value &request, Json::Value &response);
	static int getSensorSetting(Json::Value &request, Json::Value &response);
	static int setSensorSetting(Json::Value &request, Json::Value &response);
};

int COrderSysterm::getDeviceSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_ALL_CURRENT_SETTINGS
	return AE_SYS_NOERROR;
}

int COrderSysterm::getBatteryLevel(Json::Value &request, Json::Value &response)
{
	//AE_GET_BATTERY_LEVEL
	response["batteryLevel"] = 75;

	return AE_SYS_NOERROR;
}

int COrderSysterm::getCameraStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_CAMERAS_STATUS
	
	for (int i = 0; i < 6; i++)
	{
		response[i]["chanNo"] = i;
		response[i]["connStat"] = 0;
		response[i]["recordStatus"] = 0;
		response[i]["subRecStatus"] = 0;
		char name[12] = {0};
		snprintf(name, sizeof(name), "CH%d", i + 1);
		response[i]["name"] = std::string(name);
	}

	return AE_SYS_NOERROR;
}

int COrderSysterm::getGSensorData(Json::Value &request, Json::Value &response)
{
	//AE_GET_GSENSOR_DATA
	response["accX"] = 111;
	response["accY"] = 111;
	response["accZ"] = 111;
	return AE_SYS_NOERROR;
}

int COrderSysterm::getGPSData(Json::Value &request, Json::Value &response)
{
	//AE_GET_GPS
	response["valid"] = 1;
	response["time"] = "2021-05-10 17:00:01";
	response["divisionEW"] = "E";
	response["longitude"] = 435000000;
	response["divisionNS"] = "N";
	response["latitude"] = 108000000;
	response["direction"] = 630;
	response["height"] = 200;
	response["speed"] = 80000;
	response["satellites"] = 3;
	response["precision"] = 100;
	return AE_SYS_NOERROR;
}

int COrderSysterm::getDeviceInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_DEVICE_INFO
	response["deviceType"] = "AE-CN2213-C1";
	response["firmVer"] = "V1.0.0";
	response["firmDate"] = "2016.04.15";
	response["paramVersion"] = "V1.1.1";
	response["serialNum"] = "55555555";
	response["verifyCode"] = "ABCDEF";
	response["DDR"] = 256;
	response["customID"] = "A3-xxxxxxx";
	response["hardwareVer"] = "V1.1.1";
	response["language"] = 1;
	response["MCUVer"] = "V1.1.1";
	response["fpgaVersion"] = "V1.1.1";
	response["dspVersion"] = "V1.1.1";
	response["GPSVersion"] = "V1.1.1";

	return AE_SYS_NOERROR;
}

int COrderSysterm::getVehicleInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_VEHICLE_INFO
	response["driverPhone"] = "12345678910";
	response["provinceID"] = "12345";
	response["cityID"] = "12345";
	response["manufacturerID"] = "12345";
	response["ateColor"] = 0;
	response["ateType"] = 2; //[1,13]
	response["vehCharacter"] = "self";
	response["plateNum"] = "self";
	response["terminalType"] = "a3";
	response["terminalID"] = "1234567";
	response["VIN"] = "12345";
	response["engineNum"] = "12345";
	response["serial"] = "12345";
	return AE_SYS_NOERROR;
}

int COrderSysterm::setVehicleInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_VEHICLE_INFO
	return AE_SYS_NOERROR;
}

int COrderSysterm::getDriverInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_DRIVER_INFO
	response["licenseNumber"] = "12345678910";
	response["validTime"] = "12345";
	response["qualCert"] = "12345";
	response["status"] = 1;
	response["checkInTime"] = "2016.04.15";
	response["certificationOrgan"] = "xxxxx"; //[1,13]
	response["identityID"] = "123456789";
	response["driverName"] = "self";

	return AE_SYS_NOERROR;
}

int COrderSysterm::setDriverInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_DRIVER_INFO


	return AE_SYS_NOERROR;
}

int COrderSysterm::getSatelliteInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_SATELLITE_INFO
	if (!request.isMember("type"))
	{
		response = Json::nullValue;
		return AE_PROT_INVALID_TYPE;
	}
	
	response["satelliteCount"] = 3;
	response["HDOP"] = 1.0;
	//request["type"].asUInt();
	for (int i = 0; i < 3;i++)
	{
		response["infos"][i]["index"] = i;
		response["infos"][i]["radio"] = 30;
		response["infos"][i]["type"] = 1;
		response["infos"][i]["type"] = 1;
	}
	

	
	return AE_SYS_NOERROR;
}

int COrderSysterm::getDeviceStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_DEVICE_STATUS
	if (!request.isMember("type") || !request["type"].isArray())
	{
		return -1;
	}

	for(int i = 0; i < (int)request["type"].size(); i++)
	{
		if (request["type"][i].asString() == "time")
		{
			response["time"] = "2021-05-10 17:00:01";
		}
		else if (request["type"][i].asString() == "CSQ")
		{
			response["CSQ"] = 1; // [0,31]
		}
		else if (request["type"][i].asString() == "accStatus")
		{
			response["accStatus"] = 1;
		}
		else if (request["type"][i].asString() == "locationStatus")
		{
			response["locationStatus"] = 1;
		}
		else if (request["type"][i].asString() == "bizPIfLoginStatus")
		{
			response["bizPIfLoginStatus"] = 1;
		}
	}
	return AE_SYS_NOERROR;
}

int COrderSysterm::getVehicleStatus(Json::Value &request, Json::Value &response)
{
	//AE_GET_VEHICLE_STATUS
	//if (!reqParam.isMember("type") || !reqParam["type"].isArray())
	//{
	//	return -1;
	//}

	//for(int i = 0; i < (int)reqParam["type"].size(); i++)
	//{
	//	if (reqParam["type"][i].asString() == "feedProtection")
	//	{
	//		resParam["feedProtection"] = 0;
	//	}
	//	else if (reqParam["type"][i].asString() == "gear")
	//	{
	//		resParam["gear"] = 1;
	//	}
	//}
	//"feedecStatus";
	//resParam["feedPro"] = 1;
	response["gear"] = 1;
	response["feedPro"] = 1;
	
	return AE_SYS_NOERROR;
}

int COrderSysterm::getPictureSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_PICTURE_SETTING
	if (!response.isMember("chanNo"))
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["OSDName"][0]["index"] = 1;
	response["OSDName"][0]["str"] = "channel name"; 

	return AE_SYS_NOERROR;
}
int COrderSysterm::setPictureSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_PICTURE_SETTING
	return AE_SYS_NOERROR;
}

int COrderSysterm::getCompressSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_COMPRESS_SETTING
	if (!response.isMember("chanNo") || !response.isMember("streamType"))
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	response["resolution"] = 1;
	response["aspectRatio"] = 1;
	response["encodeMode"] = 1;
	response["videoQuality"] = 1;
	response["packageFormat"] = 0;
	response["bitRateType"] = 1;
	response["audioEncodeMode"] = 1;
	response["audioBitRate"] = 1;
	response["frameRate"] = 30;
	response["audioSamplingRate"] = 1;
	response["videoType"] = 1;
	response["bitRateType"] = 1;
	response["imageQuality"] = 1;

	return AE_SYS_NOERROR;
}

int COrderSysterm::setCompressSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_COMPRESS_SETTING
	
	return AE_SYS_NOERROR;
}

int COrderSysterm::getImageSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_IMAGE_SETTING
	if (!response.isMember("chanNo") || !response.isMember("streamType"))
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["resolution"] = 0;
	response["aspectRatio"] = 0;
	response["encodeMode"] = 0;
	response["videoQuality"] = 0;
	response["distortionCalibration"] = 0;
	response["videoFormat"] = 0;
	response["packageFormat"] = 0;
	response["WDR"] = 0;
	response["linkageRec"] = 0;
	return AE_SYS_NOERROR;
}

int COrderSysterm::setImageSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_IMAGE_SETTING
	return AE_SYS_NOERROR;
}

int COrderSysterm::getGenericSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_GENERIC_SETTING
	response["language"] = 0;
	response["LCDRotate"] = 0;
	response["LCDPoweroff"] = 0;
	response["shutdownDelay"] = 0;
	response["plateNumber"] = "浙A22455";
	response["trainInfo"] = "aa/bbb-ccc";
	response["btnPressTip"] = 0;
	response["speakerSwitch"] = 0;
	response["volume"] = 0;
	response["waterMark"] = 0;
	response["touchTip"] = 0;
	response["enterScreenSaverTime"] = 0;
	response["recordMode"] = 0;

	return AE_SYS_NOERROR;
}

int COrderSysterm::setGenericSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_GENERIC_SETTING

	return AE_SYS_NOERROR;
}

int COrderSysterm::getPromptSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_PROMPT_SETTING
	response["lightOnPrompt"] = 0;
	response["greenLightPrompt"] = 0;
	response["frontVehicleStartingPrompt"] = 0;
	response["motionDetect"] = 0;
	response["speedLimitDetection"] = 0;

	return AE_SYS_NOERROR;
}

int COrderSysterm::setPromptSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_PROMPT_SETTING
	return AE_SYS_NOERROR;
}

//		AE_GET_SENSOR_SETTING = 198,  /*获取传感设置*/
//		AE_SET_SENSOR_SETTING = 199,  /*设置传感设置*/
int COrderSysterm::getAlertSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_ALERT_SETTING
	response["fatigueDrivingAlert"] = 0;
	response["speedingPrompt"] = 0;
	response["SDAbnormalTip"] = 0;

	return AE_SYS_NOERROR;
}

int COrderSysterm::setAlertSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_ALERT_SETTING
	return AE_SYS_NOERROR;
}

int COrderSysterm::getSensorSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_SENSOR_SETTING
	response["gSensorSensitity"] = 0;
	response["parkingSurveillance"] = 0;
	response["parkMontorThreshold"] = "80";
	response["gps"] = 0;
	return AE_SYS_NOERROR;
}

int COrderSysterm::setSensorSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_SENSOR_SETTING
	return AE_SYS_NOERROR;
}

class COrderMedia : public IOrder
{
	//媒体类命令
public:
	virtual ~COrderMedia() {};

	static int recordStart(Json::Value &request, Json::Value &response);
	static int recordStop(Json::Value &request, Json::Value &response);
	static int eventRecordStart(Json::Value &request, Json::Value &response);
	static int audioRecordStart(Json::Value &request, Json::Value &response);
	static int audioRecordStop(Json::Value &request, Json::Value &response);
};

int COrderMedia::recordStart(Json::Value &request, Json::Value &response)
{
	//	AE_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::recordStop(Json::Value &request, Json::Value &response)
{
	//	AE_RECORD_STOP
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}

	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::eventRecordStart(Json::Value &request, Json::Value &response)
{
	//	AE_EVENT_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::audioRecordStart(Json::Value &request, Json::Value &response)
{
	//	AE_AUDIO_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::audioRecordStop(Json::Value &request, Json::Value &response)
{
	//	AE_AUDIO_RECORD_STOP
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

class COrderNetwork : public IOrder
{
	//网络类命令
public:
	virtual ~COrderNetwork() {};

	static int wifiRestart(Json::Value &request, Json::Value &response);
	static int getSTAParam(Json::Value &request, Json::Value &response);
	static int setSTAParam(Json::Value &request, Json::Value &response);
	static int getAPParam(Json::Value &request, Json::Value &response);
	static int setAPParam(Json::Value &request, Json::Value &response);
	static int get4GParam(Json::Value &request, Json::Value &response);
	static int set4GParam(Json::Value &request, Json::Value &response);
	static int getNetworkSetting(Json::Value &request, Json::Value &response);
	static int setNetworkSetting(Json::Value &request, Json::Value &response);
};

int COrderNetwork::wifiRestart(Json::Value &request, Json::Value &response)
{
	//AE_WIFI_RESTART
	return AE_SYS_NOERROR;
}

int COrderNetwork::getSTAParam(Json::Value &request, Json::Value &response)
{
	//AE_GET_STA_PARAM
	response["ssid"] = "ADAS-DACD";
	response["password"] = "0123456789";
	response["frequency"] = 1;
	return AE_SYS_NOERROR;
}

int COrderNetwork::setSTAParam(Json::Value &request, Json::Value &response)
{
	//AE_SET_STA_PARAM
	if (!response.isMember("ssid") || !response["ssid"].isString()
		|| !response.isMember("password") || !response["password"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderNetwork::getAPParam(Json::Value &request, Json::Value &response)
{
	//AE_GET_AP_PARAM
	response["ssid"] = "ADAS-DACD";
	response["password"] = "0123456789";
	response["frequency"] = 1;
	return AE_SYS_NOERROR;
}

int COrderNetwork::setAPParam(Json::Value &request, Json::Value &response)
{
	//AE_SET_AP_PARAM
	if (!response.isMember("ssid") || !response["ssid"].isString()
		|| !response.isMember("password") || !response["password"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderNetwork::get4GParam(Json::Value &request, Json::Value &response)
{
	//AE_GET_4G_PARAM
	response["enable"] = 1;
	response["apn"] = "this is an apn";
	response["telephone"] = "12345678910";
	response["username"] = "admin";
	response["password"] = "12345678";
	response["mtu"] = "1500";
	response["verify"] = 0;
	response["band"] = 0;
	response["signal"] = 80;
	response["ip"] = "192.168.1.1";
	response["simStatus"] = 1;
	return AE_SYS_NOERROR;
}

int COrderNetwork::set4GParam(Json::Value &request, Json::Value &response)
{
	//AE_SET_4G_PARAM
	if (!response.isMember("enable") || !response["enable"].isInt()
		|| !response.isMember("apn") || !response["apn"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderNetwork::getNetworkSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_NETWORK_SETTING

	response["mobileData"] = 0;
	response["wifiShutdown"] = 0;
	response["wifiMode"] = 0;
	return AE_SYS_NOERROR;
}

int COrderNetwork::setNetworkSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_NETWORK_SETTING
	return AE_SYS_NOERROR;
}

class COrderStorage : public IOrder
{
	//存储类命令
public:
	virtual ~COrderStorage() {};

	static int getSDLetter(Json::Value &request, Json::Value &response);
	static int getSDInfo(Json::Value &request, Json::Value &response);
	static int setSDLockStatus(Json::Value &request, Json::Value &response);
	static int setSDPassword(Json::Value &request, Json::Value &response);
	static int formatSD(Json::Value &request, Json::Value &response);
	static int getRecodeSchedule(Json::Value &request, Json::Value &response);
	static int setRecodeSchedule(Json::Value &request, Json::Value &response);
	static int copyDaySchedule(Json::Value &request, Json::Value &response);
	static int copyChannelSchedule(Json::Value &request, Json::Value &response);
	static int getStorageSetting(Json::Value &request, Json::Value &response);
	static int setStorageSetting(Json::Value &request, Json::Value &response);
	static int exportMediaFile(Json::Value &request, Json::Value &response);
	static int exportMediaLog(Json::Value &request, Json::Value &response);
	static int exportConfig(Json::Value &request, Json::Value &response);
	static int importConfig(Json::Value &request, Json::Value &response);
	static int cancelExport(Json::Value &request, Json::Value &response);
};

int COrderStorage::getSDLetter(Json::Value &request, Json::Value &response)
{
	//AE_GET_SD_LETTER
	response["list"][0] = "A";
	response["list"][1] = "B";
	return AE_SYS_NOERROR;
}

int COrderStorage::getSDInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_SD_INFO
	if (!request.isMember("driver") || !request["driver"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["totalSpace"] = 30424;
	response["freeSpace"] = 29650;
	response["residualLife"] = "99";
	response["healthStatus"] = "good";
	response["status"] = "nonsupport";
	return AE_SYS_NOERROR;

}
int COrderStorage::setSDLockStatus(Json::Value &request, Json::Value &response)
{
	//AE_SET_SD_LOCK_STATUS
	if (!request.isMember("SDEncrypt") || !request["SDEncrypt"].isString()
		|| !request.isMember("reset") || !request["reset"].isString()
		|| !request.isMember("driver") || !request["driver"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderStorage::setSDPassword(Json::Value &request, Json::Value &response)
{
	//AE_SET_SD_PASSWD
	if (!request.isMember("oldPasswd") || !request["oldPasswd"].isString()
		|| !request.isMember("sdPasswd") || !request["sdPasswd"].isString()
		|| !request.isMember("driver") || !request["driver"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderStorage::formatSD(Json::Value &request, Json::Value &response)
{
	//AE_FORMAT
	if (!request.isMember("driver") || !request["driver"].isString()
		|| !request.isMember("sdPasswd") || !request["sdPasswd"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::getRecodeSchedule(Json::Value &request, Json::Value &response)
{
	//AE_GET_RECORD_SCHEDILE
	if (!request.isMember("day") || !request["day"].isInt()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	int chanNo = request["chanNo"].asInt();
	response["chanNo"] = chanNo;
	response["listing"][0]["day"] = 1;
	response["listing"][0]["timeslots"][0]["type"] = 1;
	response["listing"][0]["timeslots"][0]["startTime"] = "00:00:00";
	response["listing"][0]["timeslots"][0]["ensTime"] = "23:59:59";
	
	response["listing"][1]["day"] = 2;
	response["listing"][1]["timeslots"][0]["type"] = 1;
	response["listing"][1]["timeslots"][0]["startTime"] = "00:00:00";
	response["listing"][1]["timeslots"][0]["ensTime"] = "23:59:59";
	return AE_SYS_NOERROR;
}

int COrderStorage::setRecodeSchedule(Json::Value &request, Json::Value &response)
{
	//AE_SET_RECORD_SCHEDILE
	if (!request.isMember("chanNo") || !request["chanNo"].isInt()
		|| !request.isMember("listing") || !request["listing"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::copyDaySchedule(Json::Value &request, Json::Value &response)
{
	//AE_COPY_DAY_SCHEDILE
	if (!request.isMember("fromDay") || !request["fromDay"].isInt()
		|| !request.isMember("toDay") || !request["toDay"].isArray()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::copyChannelSchedule(Json::Value &request, Json::Value &response)
{
	//AE_COPY_CHANNEL_SCHEDILE
	if (!request.isMember("fromChan") || !request["fromChan"].isInt()
		|| !request.isMember("toChan") || !request["toChan"].isArray())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::exportMediaFile(Json::Value &request, Json::Value &response)
{
	//AE_EXPORT_MEDIA_FILE
	if (!request.isMember("exportDevice") || !request["exportDevice"].isString()
		|| !request.isMember("chanNo") || !request["chanNo"].isInt())

	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	// !request.isMember("timeSlot") || !request["timeSlot"].isArray()
	//!request.isMember("filelist") || !request["filelist"].isArray()
	response["filelist"][0]["result"] = 1;
	response["filelist"][0]["name"] = "a.mp4";
	return AE_SYS_NOERROR;
}

int COrderStorage::exportMediaLog(Json::Value &request, Json::Value &response)
{
	//AE_EXPORT_LOG
	if (!request.isMember("exportDevice") || !request["exportDevice"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	if (request.isMember("timeSlot") && request["timeSlot"].isArray())
	{
		for (int i = 0; i < (int)request["timeSlot"].size(); i++)
		{
			if (!request["timeSlot"][i].isMember("startTime") 
				|| !request["timeSlot"][i]["startTime"].isString()
				|| !request["timeSlot"][i].isMember("endTime")
				|| !request["timeSlot"][i]["endTime"].isString())
			{
				response == Json::nullValue;
				return AE_SYS_UNKNOWN_ERROR;
			}
		}
	} 

	response["filelist"][0]["result"] = 1;
	response["filelist"][0]["name"] = "a.mp4";
	return AE_SYS_NOERROR;
}

int COrderStorage::exportConfig(Json::Value &request, Json::Value &response)
{
	//AE_EXPORT_CONFIG
	if (!request.isMember("type") || !request["type"].isInt()
		|| !request.isMember("exportDevice") ||request["exportDevice"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::importConfig(Json::Value &request, Json::Value &response)
{
	//AE_IMPORT_CONFIG
	if (!request.isMember("type") || !request["type"].isInt()
		|| !request.isMember("importDevice") ||request["importDevice"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::cancelExport(Json::Value &request, Json::Value &response)
{
	//AE_CONCEL_EXPORT
	if (!request.isMember("type") || !request["type"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderStorage::getStorageSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_STORAGE_SETTING
	response["clipDuration"] = 1;
	response["microphone"] = 1;
	response["cycleRecord"] = 1;
	response["subRec"] = 1;
	return AE_SYS_NOERROR;
}

int COrderStorage::setStorageSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_STORAGE_SETTING
	return AE_SYS_NOERROR;
}

class COrderTime : public IOrder
{
	//时间类命令
public:
	virtual ~COrderTime() {};

	static int getDayLightTime(Json::Value &request, Json::Value &response);
	static int setDayLightTime(Json::Value &request, Json::Value &response);
	static int getTimeZone(Json::Value &request, Json::Value &response);
	static int setTimeZone(Json::Value &request, Json::Value &response);
	static int getTimeSetting(Json::Value &request, Json::Value &response);
	static int setTimeSetting(Json::Value &request, Json::Value &response);
};

int COrderTime::getDayLightTime(Json::Value &request, Json::Value &response)
{
	//AE_GET_DAYLIGHT_TIME
	
	response["DST"] = 1;
	response["startDate"] = "m04.5.1";
	response["endDate"] = "m04.5.1";
	response["startTime"] = "20:17";
	response["endTime"] = "20:17";
	response["DSTBias"] = "60";
	return AE_SYS_NOERROR;
}

int COrderTime::setDayLightTime(Json::Value &request, Json::Value &response)
{
	//AE_SET_DAYLIGHT_TIME
	if (!request.isMember("DST") || !request["DST"].isInt()
		|| request.isMember("startDate") || !request["startDate"].isString()
		|| request.isMember("endDate") || !request["endDate"].isString()
		|| request.isMember("startTime") || !request["startTime"].isString()
		|| request.isMember("endTime") || !request["endTime"].isString()
		|| request.isMember("DSTBias") || !request["DSTBias"].isString()
		)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderTime::getTimeZone(Json::Value &request, Json::Value &response)
{
	//AE_GET_TIMEZONE
	response["timeZone"] = "GMT+08:00";
	return AE_SYS_NOERROR;
}

int COrderTime::setTimeZone(Json::Value &request, Json::Value &response)
{
	//AE_SET_TIMEZONE
	if (!request.isMember("timeZone") || !request["timeZone"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderTime::getTimeSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_TIME_SETTING
	response["dateTime"] = "2021-01-01 10:10:10";
	response["DST"] = 0;
	response["startDate"] = "m04.5.1";
	response["endDate"] = "m04.5.1";
	response["startTime"] = "20:17";
	response["endTime"] = "20:17";
	response["DSTBias"] = "60";
	response["timeZone"] = "GMT+08:00";
	return AE_SYS_NOERROR;
}

int COrderTime::setTimeSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_TIME_SETTING
	return AE_SYS_NOERROR;
}

bool IOrder::orderHub(unsigned int msgID, Json::Value &request, Json::Value &response)
{
	printf("\033[35m""msgID = %d""\033[0m\n", msgID);
	
	Json::Value reqParam = Json::nullValue;
	Json::Value resParam = Json::nullValue;
	if (request.isMember("param"))
	{
		reqParam.swap(request["param"]);
	}
	
	bool ret = false;
	int res = 0;
	switch(msgID)
	{
			case AE_GET_CAMERAS_STATUS:
				res = COrderSysterm::getCameraStatus(reqParam, resParam);
				break;

			case AE_GET_VEHICLE_STATUS:
				//res = getVehicleStatus(reqParam, resParam);
				break;
			case AE_SEND_APP_INFO:
				//res = sendAppInfo(reqParam, resParam);
				break;
			default: 
				res = -1;
				break;
	}
	
	if (resParam != Json::nullValue)
	{
		response["param"].swap(resParam["param"]);
	}

	ret = (res==0);

	response["rval"] = res;
	response["msgId"] = request["msgId"].asUInt();
	response["token"] = request["token"].asUInt();
	return ret;
}


CNetProtocl::CNetProtocl(Terminal::ITerminal* terminal)
:m_pTerminal(terminal)
{

}

CNetProtocl::~CNetProtocl()
{
}


bool CNetProtocl::parse(ISession * session, char* buf, int len)
{
	if (session->getState() == ISession::emStateLogin)
	{
		messageProcess(session, buf, len);
		printf("\033[35m""%s:%d %s ""\033[0m\n",__FILE__, __LINE__, __FUNCTION__);
		return true;
	}
	else
	{
		return handShake(session, buf, len);
	}
}

bool CNetProtocl::messageProcess(NetServer::ISession* session, char* buf, int len)
{
		bool res = false;
		unsigned int uReqIdx = 0;
		unsigned int uDateLen = 0;
		if (!headerCheck(buf, &uReqIdx, &uDateLen))
		{
			printf("\033[35m""header Check err""\033[0m\n");
			return false;
		}

		char dataBuf[NET_APP_RECV_SIZE] = {0};
		int uLen = 0;
		decrypt(buf + sizeof(struct msgHeader), uDateLen, dataBuf, &uLen);
		std::string recv = dataBuf;
		Json::String errs;
		Json::Value request;
		Json::CharReaderBuilder readerBuilder;
		std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
		res = jsonReader->parse(recv.c_str(), recv.c_str() + recv.length(), &request, &errs);
		if (!res || !errs.empty())
		{
			printf("\033[35m""parse:%s""\033[0m\n", errs.c_str());
			return false;
		}
	
		printf("\033[35m""request = %s""\033[0m\n", request.toStyledString().c_str());

		if (request.isMember("token") && request.isMember("msgId"))
		{
			Param_t stParam;
			stParam.uTokenId = request["token"].asUInt();
			stParam.uMsgId = request["msgId"].asUInt();
			stParam.uReqIdx = uReqIdx;
			stParam.uEncrypt = 0;

			Json::Value response = Json::nullValue;
			res = msgHub(session, stParam.uMsgId, request, response);
			if (res)
			{
				printf("\033[35m""response = %s""\033[0m\n", response.toStyledString().c_str());
				std::ostringstream os;
				Json::StreamWriterBuilder writerBuilder;
				writerBuilder["indentation"] = "";
				std::unique_ptr<Json::StreamWriter> const jsonWriter(writerBuilder.newStreamWriter());
				jsonWriter->write(response, &os);
				std::string reString = os.str();
				reString += " ";

				//printf("\033[35m""reString = %s""\033[0m\n", reString.c_str());
				//printf("\033[35m""reString = %d""\033[0m\n", reString.length());
				//printf("\033[35m""reString = %c""\033[0m\n", reString[reString.length()]);
				reply(session, &stParam, reString.c_str(), reString.length());
					//writerBuilder["indentation"] = "\t";
				return true;
			}
			res = false;
		}
		else
		{
			res = false;
		}


		return res;

}

bool CNetProtocl::msgHub(ISession* session, unsigned int msgID, Json::Value &request, Json::Value &response)
{
	bool ret = false;
	/*
	printf("\033[35m""msgID = %d""\033[0m\n", msgID);
	bool ret = false;
	if (!request.isMember("param"))
	{

		switch(msgID)
		{
			case IOrder::AE_STOP_SESSION:
				ret = logout(session, request, response);
				break;
			case IOrder::AE_GET_CAMERAS_STATUS:
				ret = getCameraStatus(session, request, response);
				break;
			default: break;
		}
	}
	else
	{
		int res = 0;
		Json::Value & reqParam = request["param"];
		Json::Value & resParam = response["param"];
		switch(msgID)
		{
			case IOrder::AE_GET_SETTING:
				res = getSetting(session, reqParam, resParam);
				break;

			case IOrder::AE_GET_VEHICLE_STATUS:
				res = getVehicleStatus(session, reqParam, resParam);
				break;
			case IOrder::AE_SEND_APP_INFO:
				res = sendAppInfo(session, reqParam, resParam);
				break;
			default: 
				res = -1;
				break;
		}
		
		ret = (res==0);

		response["rval"] = res;
		response["msgId"] = request["msgId"].asUInt();
		response["token"] = request["token"].asUInt();
	}
*/
	ret = IOrder::orderHub(msgID, request, response);
	return ret;
}

bool CNetProtocl::login(ISession* session, Json::Value &request, Json::Value &response)
{

	std::string rsaKey = request["rsaKey"].asString();

	response["rval"] = 0;
	response["msg_id"] = request["msg_id"].asUInt();
	response["param"] = 1;//TokenNumber
	response["version"] = "V1.1.0";
	
	char sRsaEncodeKey[300] = {0};
 	char sKeyStr[100] = {0};
	
	memset(m_AesKey, 0, aesKeyLength);
	RAND_pseudo_bytes(m_AesKey, aesKeyLength);

	for (size_t i = 0; i < aesKeyLength; i++)
	{
		sprintf(sKeyStr + i * 2, "%02x", m_AesKey[i]);
	}
	int iRet = app_rsa_encode(rsaKey.c_str(), sKeyStr, (unsigned char *)sRsaEncodeKey);
	if (iRet < 0)
	{
		return false;
	}

	response["aesCode"] = std::string(sRsaEncodeKey);

	response["timeout"] = 15;
	response["productType"] = 0;

	m_pTerminal->connect(session);

	return session->login();
}

bool CNetProtocl::logout(NetServer::ISession* session, Json::Value &request, Json::Value &response)
{
	m_pTerminal->disconnet(session);
	return session->logout();
}

bool CNetProtocl::keepAlive(NetServer::ISession* session, Json::Value &request, Json::Value &response)
{
	return session->keepAlive();
}

bool CNetProtocl::handShake(NetServer::ISession* session, char* buf, int len)
{
		std::string recv = buf;
		Json::String errs;
		Json::Value request;
		Json::CharReaderBuilder readerBuilder;
		
		std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
		bool res = jsonReader->parse(recv.c_str(), recv.c_str() + recv.length(), &request, &errs);
		if (!res || !errs.empty())
		{
			return false;
		}
		
		printf("\033[35m""request = %s""\033[0m\n", request.toStyledString().c_str());

		if (request.isMember("token") && request.isMember("msg_id") && request["msg_id"].asUInt() == IOrder::AE_START_SESSION)
		{
			Json::Value response = Json::nullValue;

			if (login(session, request, response))
			{
				printf("\033[35m""response = %s""\033[0m\n", response.toStyledString().c_str());

				std::string reString = response.toStyledString().c_str();

				session->send(reString.c_str(), reString.length());
				return true;
			}
		}

		return false;
}

bool CNetProtocl::headerCheck(const char *buf, unsigned int *index, unsigned int * len)
{
	struct msgHeader* pHeader = (struct msgHeader*)buf;

	if (pHeader->uMsgConstant != htonl(MSG_HEADER_CONS))
	{
		return false;
	}
	else
	{
		*index = ntohl(pHeader->uMsgIndex);
		*len = ntohl(pHeader->uMsgLength);
		return true;
	}
	/*//消息头：ABBC，前4个字节
	if (buf[0] != 0x41 || buf[1] != 0x42 || buf[2] != 0x42 || buf[3] != 0x43)
	{
		return false;
	}
	else
	{
		//获取消息索引，跳过消息头再取4个字节
		*index = (buf[4] << 24) + (buf[5] << 16) + (buf[6] << 8) + buf[7];
		//获取消息长度，跳过消息头及索引再取4个字节
		*len = (buf[8] << 24) + (buf[9] << 16) + (buf[10] << 8) + buf[11];
		return true;
	}
	*/
}


#ifndef ROUND_UP
#define ROUND_UP(x, align)       (((int)(x) + (align - 1)) & ~(align - 1))
#endif

#ifndef ROUND_DOWN
#define ROUND_DOWN(x, align)    ((int)(x) & ~(align - 1))
#endif

bool CNetProtocl::decrypt(const char* buf, int len, char* decodeBuf, int* Length)
{

	char baseBuf[NET_APP_RECV_SIZE] = {0};
	
	int iBaseLen = EVP_DecodeBlock((unsigned char*)baseBuf, (const unsigned char*)buf, len);
	int iAesLen = ROUND_UP(iBaseLen, aesKeyLength);

	int iRet = aes_decrypt(baseBuf, iAesLen, decodeBuf, NET_APP_RECV_ADD, Length, m_AesKey);
	if (iRet < 0)
	{
		printf("\033[35m""aes decrypt failed""\033[0m\n");
		return false;
	}

	return true;
}

bool CNetProtocl::encrypt(const char* buf, int len, char* encryptBuf, int* Length)
{
	return true;
}

bool CNetProtocl::reply(NetServer::ISession* session, Param_t* param, const char *buf, int len)
{
	unsigned char sAesOut[AES_MAX_OUT_LEN] = {0};
	char sendbuf[AES_MAX_OUT_LEN_BASE64] = {0};

	if(len > AES_MAX_IN_LEN)
	{
		printf("\033[35m""encrypt str too large""\033[0m\n");
		return false;
	}

	int iAesOutLen = 0;
	int iRet = aes_encrypt((unsigned char*)buf, AES_MAX_IN_LEN, len, sAesOut, AES_MAX_OUT_LEN, &iAesOutLen, m_AesKey);
	if(iRet < 0)
	{
		printf("\033[35m""app_aes_encrypt ERR: %d""\033[0m\n", iRet);
		return false;
	}

	if (iAesOutLen > AES_MAX_IN_LEN)
	{
		printf("\033[35m""encode str too large""\033[0m\n");
		return false;
	}
	
	struct msgHeader* pHeader = (struct msgHeader*)sendbuf;
	char* pMsgBody = (sendbuf + sizeof(struct msgHeader));
	int iBase64OutLen = EVP_EncodeBlock((unsigned char *)pMsgBody, sAesOut, iAesOutLen); //base64编码

	pHeader->uMsgConstant = htonl(MSG_HEADER_CONS);
	pHeader->uMsgIndex = htonl(param->uReqIdx);
	pHeader->uMsgLength = htonl(iBase64OutLen);
	int iDataLen = strlen(pMsgBody) + sizeof(struct msgHeader);

	session->send(sendbuf, iDataLen);
	return true;
}

int CNetProtocl::getSetting(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	if (!reqParam.isMember("chanNo") || !reqParam.isMember("type"))
	{
		return -1;
	}

	unsigned int chanNo = reqParam["chanNo"].asUInt();
	std::string type = reqParam["type"].asString();

	resParam["chanNo"] = chanNo;
	resParam["type"] = type;
	
	if (type == "dateTime")
	{
		resParam["value"] = "2021-05-10 17:00:01";
	}
	
	return 0;
}

bool CNetProtocl::getCameraStatus(NetServer::ISession* session, Json::Value &request, Json::Value &response)
{
	Json::Value &resParam = response["param"];
	for(int i = 0; i < 6; i++)
	{
		resParam[i]["chanNo"] = i;
		resParam[i]["connStat"] = 0;
		resParam[i]["recordStatus"] = 0;
		resParam[i]["subRecStatus"] = 0;
		char name[12] = {0};
		snprintf(name, sizeof(name), "CH%d", i+1);
		resParam[i]["name"] = std::string(name);
	}
	
	response["rval"] = 0u;
	response["msgId"] = request["msgId"].asUInt();
	response["token"] = request["token"].asUInt();
	return true;
}

int CNetProtocl::getVehicleStatus(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	
	//if (!reqParam.isMember("type") || !reqParam["type"].isArray())
	//{
	//	return -1;
	//}

	//for(int i = 0; i < (int)reqParam["type"].size(); i++)
	//{
	//	if (reqParam["type"][i].asString() == "feedProtection")
	//	{
	//		resParam["feedProtection"] = 0;
	//	}
	//	else if (reqParam["type"][i].asString() == "gear")
	//	{
	//		resParam["gear"] = 1;
	//	}
	//}
	//"feedecStatus";
	//resParam["feedPro"] = 1;
	resParam["gear"] = 1;
	resParam["feedPro"] = 1;
	
	return 0;
}

int CNetProtocl::getDeviceStatus(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	//AE_GET_DEVICE_STATUS
	if (!reqParam.isMember("type") || !reqParam["type"].isArray())
	{
		return -1;
	}

	for(int i = 0; i < (int)reqParam["type"].size(); i++)
	{
		if (reqParam["type"][i].asString() == "time")
		{
			resParam["time"] = "2021-05-10 17:00:01";
		}
		else if (reqParam["type"][i].asString() == "CSQ")
		{
			resParam["CSQ"] = 1; // [0,31]
		}
		else if (reqParam["type"][i].asString() == "accStatus")
		{
			resParam["accStatus"] = 1;
		}
		else if (reqParam["type"][i].asString() == "locationStatus")
		{
			resParam["locationStatus"] = 1;
		}
		else if (reqParam["type"][i].asString() == "bizPIfLoginStatus")
		{
			resParam["bizPIfLoginStatus"] = 1;
		}
	}
	return 0;
}

int CNetProtocl::sendAppInfo(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	
	if (!reqParam.isMember("version"))
	{
		return -1;
	}

	resParam = Json::nullValue;

	return 0;
}

int CNetProtocl::sendTouchInfo(NetServer::ISession* session, Json::Value &reqParam, Json::Value &resParam)
{
	//AE_SEND_TOUCH_INFO
	if (!reqParam.isMember("touchX") || !reqParam.isMember("touchY") 
	|| !reqParam.isMember("screenWidth") || !reqParam.isMember("screenHeight") || !reqParam.isMember("touchType"))
	{
		return -1;
	}

	resParam = Json::nullValue;
	return 0;
}

}//Screen
