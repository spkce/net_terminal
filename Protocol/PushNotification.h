#ifndef __PUSH_NOTIFICASION_H__
#define __PUSH_NOTIFICASION_H__

#include "Order.h"

namespace Screen
{

class CPushNotification : public IOrder
{
	//Õ∆ÀÕ¿‡√¸¡Ó
public:
	virtual ~CPushNotification() {};

	static int notification(char* buf, int len, Json::Value &send);
	static int sendWarnInfo(char* buf, int len, Json::Value &send);
	static int sendCheckInfo(char* buf, int len, Json::Value &send);
	static int sendClientMessage(char* buf, int len, Json::Value &send);
	
};

}//Screen
#endif
