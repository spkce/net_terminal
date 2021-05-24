#ifndef __ORDER_PLATFORM_H__
#define __ORDER_PLATFORM_H__

#include "Order.h"

namespace Screen
{

class COrderPlatform : public IOrder
{
	//∆ΩÃ®¿‡√¸¡Ó
public:
	virtual ~COrderPlatform() {};

	static int getPlatformConnInfo(Json::Value &request, Json::Value &response);
	static int setPlatformConnInfo(Json::Value &request, Json::Value &response);
	static int get808ConnInfo(Json::Value &request, Json::Value &response);
	static int set808ConnInfo(Json::Value &request, Json::Value &response);
	static int get808ConnInfo2(Json::Value &request, Json::Value &response);
	static int set808ConnInfo2(Json::Value &request, Json::Value &response);
	static int getOperateConnInfo(Json::Value &request, Json::Value &response);
	static int setOperateConnInfo(Json::Value &request, Json::Value &response);
	static int getNtpConnInfo(Json::Value &request, Json::Value &response);
	static int setNtpConnInfo(Json::Value &request, Json::Value &response);
};

}//Screen

#endif //__ORDER_PLATFORM_H__
