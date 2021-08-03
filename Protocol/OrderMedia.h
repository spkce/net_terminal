#ifndef __ORDER_MEDIA_H__
#define __ORDER_MEDIA_H__

#include "Order.h"

namespace Screen
{

class COrderMedia : public IOrder
{
	//√ΩÃÂ¿‡√¸¡Ó
public:
	virtual ~COrderMedia() {};

	static int recordStart(Json::Value &request, Json::Value &response);
	static int recordStop(Json::Value &request, Json::Value &response);
	static int eventRecordStart(Json::Value &request, Json::Value &response);
	static int audioRecordStart(Json::Value &request, Json::Value &response);
	static int audioRecordStop(Json::Value &request, Json::Value &response);
	static int takePhoto(Json::Value &request, Json::Value &response);
	static int getVideoFileList(Json::Value &request, Json::Value &response);
};

}//Screen

#endif //__ORDER_MEDIA_H__
