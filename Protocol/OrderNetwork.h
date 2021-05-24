#ifndef __ORDER_NETWORK_H__
#define __ORDER_NETWORK_H__

#include "Order.h"

namespace Screen
{

class COrderNetwork : public IOrder
{
	//Õ¯¬Á¿‡√¸¡Ó
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

}//Screen

#endif //__ORDER_NETWORK_H__
