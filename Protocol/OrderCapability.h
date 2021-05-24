#ifndef __ORDER_CAPABILITY_H__
#define __ORDER_CAPABILITY_H__

#include "Order.h"

namespace Screen
{

class COrderCapability : public IOrder
{
	//能力集类命令
public:
	virtual ~COrderCapability() {};

	static int getCapability(Json::Value &request, Json::Value &response);
	static int getCapabilityImage(Json::Value &request, Json::Value &response);
	static int getCapabilityBasic(Json::Value &request, Json::Value &response);
	static int getCapabilityNetwork(Json::Value &request, Json::Value &response);
	//static int getCapabilityStorage(Json::Value &request, Json::Value &response);
	//static int getCapabilityIntelligence(Json::Value &request, Json::Value &response);
	//static int getCapabilityPrompt(Json::Value &request, Json::Value &response);
	//static int getCapabilityAlert(Json::Value &request, Json::Value &response);
	//static int getCapabilitySensor(Json::Value &request, Json::Value &response);
	//static int getCapabilityADAS(Json::Value &request, Json::Value &response);
	//static int getCapabilityDBA(Json::Value &request, Json::Value &response);
	//static int getCapabilityVSD(Json::Value &request, Json::Value &response);
	//static int getCapabilityBSD(Json::Value &request, Json::Value &response);
	//static int getCapabilityFace(Json::Value &request, Json::Value &response);
	//static int getCapabilityTime(Json::Value &request, Json::Value &response);
	//static int getCapabilityWHD(Json::Value &request, Json::Value &response);
	//static int getCapabilityPicture(Json::Value &request, Json::Value &response);
	//static int getCapabilityCompress(Json::Value &request, Json::Value &response);
	//static int getCapabilityBluetooth(Json::Value &request, Json::Value &response);
	//static int getCapabilityIPC(Json::Value &request, Json::Value &response);
};

}//Screen

#endif //__ORDER_CAPABILITY_H__
