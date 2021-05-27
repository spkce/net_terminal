#ifndef __ORDER_NOTIFY_H__
#define __ORDER_NOTIFY_H__

#include "Order.h"

namespace Screen
{

class COrderNotify : public IOrder
{
	//Õ®÷™¿‡√¸¡Ó
public:
	virtual ~COrderNotify() {};

	static int sendTouchInfo(Json::Value &request, Json::Value &response);

};

}//Screen

#endif //__ORDER_NOTIFY_H__
