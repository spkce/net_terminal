#ifndef __PUSH_NOTIFICASION_H__
#define __PUSH_NOTIFICASION_H__

#include "Order.h"

namespace Screen
{

class CPushNotification : public IOrder
{
	//����������
public:
	virtual ~CPushNotification() {};

	static int sendWarnInfo(char* buf, int len, Json::Value &send);
};

}//Screen
#endif