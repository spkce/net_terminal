#ifndef __ORDER_PERIPHERAL_H__
#define __ORDER_PERIPHERAL_H__

#include "Order.h"

namespace Screen
{

class COrderPeripheral : public IOrder
{
	//外接设备类命令
public:
	virtual ~COrderPeripheral() {};

	static int getAddedIPCList(Json::Value &request, Json::Value &response);
	static int setAddableIPCList(Json::Value &request, Json::Value &response);
	static int addIPC(Json::Value &request, Json::Value &response);
	static int delIPC(Json::Value &request, Json::Value &response);
	static int getPeripheralStatus(Json::Value &request, Json::Value &response);
};

}//Screen

#endif //__ORDER_PERIPHERAL_H__
