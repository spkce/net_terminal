#ifndef __ORDER_SYSTERM_H__
#define __ORDER_SYSTERM_H__

#include "Order.h"

namespace Screen
{

class COrderSysterm : public IOrder
{
public:
	/**
	* @brief 析构函数
	**/
	virtual ~COrderSysterm() {};
	/**
	* @brief 获取所有设置的当前参数
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getDeviceSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取电池状态
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getBatteryLevel(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取所有通道接入和录像状态
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getCameraStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取设备G-sensor数据
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getGSensorData(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取当前GPS坐标
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getGPSData(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取设备信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getDeviceInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取车辆相关信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getVehicleInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置车辆相关信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setVehicleInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取驾驶员相关信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getDriverInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置驾驶员相关信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setDriverInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取车辆状态
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getCarStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取设备当前的搜星信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getSatelliteInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取设备状态
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getDeviceStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取车辆状态
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getVehicleStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取图像设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getPictureSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置图像设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setPictureSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取压缩设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getCompressSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置压缩设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setCompressSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取压缩设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getImageSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置图片设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setImageSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取通用设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getGenericSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置通用设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setGenericSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取提醒设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getPromptSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置提醒设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setPromptSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取告警设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getAlertSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置告警设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setAlertSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取某项设置的当前参数
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getStting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取传感设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getSensorSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 设置传感设置
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int setSensorSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取许可证消息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getLicenseInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 设备启动自检
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int startSelfChecking(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取电子围栏信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int getAreaInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief 获取电子围栏信息
	* @param request 请求报文
	* @param response 回复报文
	* @return 错误码
	**/
	static int checkSelf(Json::Value &request, Json::Value &response);

};

}//Screen

#endif	//__ORDER_SYSTERM_H__
