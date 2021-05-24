#ifndef __ORDER_FACE_H__
#define __ORDER_FACE_H__

#include "Order.h"

namespace Screen
{

class COrderFace : public IOrder
{
	//»À¡≥¿‡√¸¡Ó
public:
	virtual ~COrderFace() {};

	static int getFaceInfo(Json::Value &request, Json::Value &response);
	static int setFaceInfo(Json::Value &request, Json::Value &response);
	static int getOverTimeDrivingSetting(Json::Value &request, Json::Value &response);
	static int setOverTimeDrivingSetting(Json::Value &request, Json::Value &response);
	static int faceContrast(Json::Value &request, Json::Value &response);
};

}//Screen

#endif //__ORDER_FACE_H__
