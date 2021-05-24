
#include "OrderMedia.h"

namespace Screen
{

int COrderMedia::recordStart(Json::Value &request, Json::Value &response)
{
	//	AE_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::recordStop(Json::Value &request, Json::Value &response)
{
	//	AE_RECORD_STOP
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}

	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::eventRecordStart(Json::Value &request, Json::Value &response)
{
	//	AE_EVENT_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::audioRecordStart(Json::Value &request, Json::Value &response)
{
	//	AE_AUDIO_RECORD_START
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

int COrderMedia::audioRecordStop(Json::Value &request, Json::Value &response)
{
	//	AE_AUDIO_RECORD_STOP
	if (!request.isMember("chanNo") || !request["chanNo"].isUInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	if (!request.isMember("type"))
	{
		return AE_PROT_INVALID_TYPE;
	}
	
	unsigned int chanNo = request["chanNo"].asUInt();
	response["chanNo"] = chanNo;

	return AE_SYS_NOERROR;
}

}//Screen
