#ifndef __ORDER_SMART_H__
#define __ORDER_SMART_H__

#include "Order.h"

namespace Screen
{

class COrderSmart : public IOrder
{
	//÷«ƒ‹¿‡
public:
	virtual ~COrderSmart(){};

	static int getCarStatus(Json::Value &request, Json::Value &response);
	static int getFaceInfo(Json::Value &request, Json::Value &response);
	static int setFaceInfo(Json::Value &request, Json::Value &response);
	static int faceContrast(Json::Value &request, Json::Value &response);

};

} // namespace Screen

#endif // __ORDER_SMART_H__
