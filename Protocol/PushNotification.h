#ifndef __PUSH_NOTIFICASION_H__
#define __PUSH_NOTIFICASION_H__

#include "Order.h"

namespace Screen
{

class CPushNotification : public IOrder
{
	//推送类命令
public:
	virtual ~CPushNotification() {};

	/**
	* @brief 通知
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int notification(char* buf, int len, Json::Value &send);

	/**
	* @brief 报警信息通知
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int sendWarnInfo(char* buf, int len, Json::Value &send);

	/**
	* @brief 自检信息通知
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int sendCheckInfo(char* buf, int len, Json::Value &send);

	/**
	* @brief 消息通知
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int sendClientMessage(char* buf, int len, Json::Value &send);

	/**
	* @brief 许可证通知
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int sendLicense(char* buf, int len, Json::Value &send);

	/**
	* @brief 电子围栏通知
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int sendArea(char* buf, int len, Json::Value &send);

	/**
	* @brief 清空电子围栏
	* @param buf 推送内容
	* @param len 推送内容
	* @param send 推送报文
	* @return 错误码
	**/
	static int sendClearArea(char* buf, int len, Json::Value &send);
};

}//Screen
#endif
