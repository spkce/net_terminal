#include "OrderPlatform.h"

namespace Screen
{

int COrderPlatform::getPlatformConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_PLATFORM_CONN_INFO
	if (!request.isMember("type") || !request["type"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	response["enable"] = 0;
	response["type"] = 0;
	response["ip"] = "www.baidu.com";
	response["prot"] = 80;
	response["id"] = "sssssss";
	response["status"] = 1;

	return AE_SYS_NOERROR;
}

/*设置平台信息*/
int COrderPlatform::setPlatformConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_PLATFORM_CONN_INFO
	if (!request.isMember("enable") || !request["enable"].isInt()
		||!request.isMember("type") || !request["type"].isInt()
		||!request.isMember("ip") || !request["ip"].isString()
		||!request.isMember("prot") || !request["prot"].isInt()
		||!request.isMember("id") || !request["id"].isString()
		)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderPlatform::get808ConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_808_CONN_INFO
	if (!request.isMember("platformOrder") || !request["platformOrder"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	response["enable"] = 0;
	response["type"] = 0;
	response["ip"] = "www.baidu.com";
	response["prot"] = 80;
	response["id"] = "sssssss";
	response["serial"] = "sssssss";
	response["status"] = 1;
	response["platformOrder"] = 1;
	response["uploadEnable"] = 1;
	response["protocol"] = 0;
	return AE_SYS_NOERROR;
}
int COrderPlatform::set808ConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_808_CONN_INFO
	if (!request.isMember("enable") || !request["enable"].isInt()
		||!request.isMember("type") || !request["type"].isInt()
		||!request.isMember("ip") || !request["ip"].isString()
		||!request.isMember("prot") || !request["prot"].isInt()
		||!request.isMember("id") || !request["id"].isString()
		||!request.isMember("serial") || !request["serial"].isString()
		)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}
int COrderPlatform::get808ConnInfo2(Json::Value &request, Json::Value &response)
{
	//AE_GET_808_CONN_INFO_2
	if (!request.isMember("platformOrder") || !request["platformOrder"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	response["enable"] = 0;
	response["type"] = 0;
	response["ip"] = "www.baidu.com";
	response["prot"] = 80;
	response["id"] = "sssssss";
	response["serial"] = "sssssss";
	response["status"] = 1;
	response["platformOrder"] = 1;
	response["uploadEnable"] = 1;
	response["protocol"] = 0;
	return AE_SYS_NOERROR;
}
int COrderPlatform::set808ConnInfo2(Json::Value &request, Json::Value &response)
{
	//AE_SET_808_CONN_INFO_2
	if (!request.isMember("enable") || !request["enable"].isInt()
		||!request.isMember("type") || !request["type"].isInt()
		||!request.isMember("ip") || !request["ip"].isString()
		||!request.isMember("prot") || !request["prot"].isInt()
		||!request.isMember("id") || !request["id"].isString()
		||!request.isMember("serial") || !request["serial"].isString()
		)
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderPlatform::getOperateConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_OPERATE_PLATFORM_INFO
	response["enable"] = 0;
	response["type"] = 0;
	response["ip"] = "www.baidu.com";
	return AE_SYS_NOERROR;
}

int COrderPlatform::setOperateConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_OPERATE_PLATFORM_INFO
	if (!request.isMember("enable") || !request["enable"].isInt()
		||!request.isMember("ip") || !request["ip"].isString()
		||!request.isMember("prot") || !request["prot"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderPlatform::getNtpConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_GET_NTP_PLATFORM_INFO
	if (!request.isMember("type") || !request["type"].isInt())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	
	response["enable"] = 0;
	response["ip"] = "www.baidu.com";
	response["prot"] = 80;

	return AE_SYS_NOERROR;
}

int COrderPlatform::setNtpConnInfo(Json::Value &request, Json::Value &response)
{
	//AE_SET_NTP_PLATFORM_INFO
	if (!request.isMember("enable") || !request["enable"].isInt()
		||!request.isMember("ip") || !request["ip"].isString()
		||!request.isMember("prot") || !request["prot"].isInt())
	{
			return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

}//Screen
