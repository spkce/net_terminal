#ifndef __ORDER_STORAGE_H__
#define __ORDER_STORAGE_H__

#include "Order.h"

namespace Screen
{

class COrderStorage : public IOrder
{
	//¥Ê¥¢¿‡√¸¡Ó
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

}//Screen

#endif //__ORDER_STORAGE_H__
