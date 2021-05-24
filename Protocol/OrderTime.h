#ifndef __ORDER_TIME_H__
#define __ORDER_TIME_H__

#include "Order.h"

namespace Screen
{

class COrderTime : public IOrder
{
	// ±º‰¿‡√¸¡Ó
public:
	virtual ~COrderTime() {};

	static int getDayLightTime(Json::Value &request, Json::Value &response);
	static int setDayLightTime(Json::Value &request, Json::Value &response);
	static int getTimeZone(Json::Value &request, Json::Value &response);
	static int setTimeZone(Json::Value &request, Json::Value &response);
	static int getTimeSetting(Json::Value &request, Json::Value &response);
	static int setTimeSetting(Json::Value &request, Json::Value &response);
};

}//Screen

#endif //__ORDER_TIME_H__
