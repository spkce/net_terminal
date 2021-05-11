#ifndef __CORDER_SYSTERM_H__
#define __CORDER_SYSTERM_H__

#include "IOrder.h"

namespace Screen
{
class COrderSysterm : public IOrder
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

		AE_GET_VEHICLE_STATUS = 26, /*获取设备状态*/
		AE_GET_DEVICE_STATUS = 27, /*获取车辆状态*/

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
	};

	enum ErrCode
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
public:
	COrderSysterm();
	~COrderSysterm();

	int getCameraStatus(Json::Value &request, Json::Value &response);
};



} //Screen
#endif //__CORDER_SYSTERM_H__
