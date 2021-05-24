#include "OrderNetwork.h"

namespace Screen
{
	
int COrderNetwork::wifiRestart(Json::Value &request, Json::Value &response)
{
	//AE_WIFI_RESTART
	return AE_SYS_NOERROR;
}

int COrderNetwork::getSTAParam(Json::Value &request, Json::Value &response)
{
	//AE_GET_STA_PARAM
	response["ssid"] = "ADAS-DACD";
	response["password"] = "0123456789";
	response["frequency"] = 1;
	return AE_SYS_NOERROR;
}

int COrderNetwork::setSTAParam(Json::Value &request, Json::Value &response)
{
	//AE_SET_STA_PARAM
	if (!response.isMember("ssid") || !response["ssid"].isString()
		|| !response.isMember("password") || !response["password"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}
	return AE_SYS_NOERROR;
}

int COrderNetwork::getAPParam(Json::Value &request, Json::Value &response)
{
	//AE_GET_AP_PARAM
	response["ssid"] = "ADAS-DACD";
	response["password"] = "0123456789";
	response["frequency"] = 1;
	return AE_SYS_NOERROR;
}

int COrderNetwork::setAPParam(Json::Value &request, Json::Value &response)
{
	//AE_SET_AP_PARAM
	if (!response.isMember("ssid") || !response["ssid"].isString()
		|| !response.isMember("password") || !response["password"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderNetwork::get4GParam(Json::Value &request, Json::Value &response)
{
	//AE_GET_4G_PARAM
	response["enable"] = 1;
	response["apn"] = "this is an apn";
	response["telephone"] = "12345678910";
	response["username"] = "admin";
	response["password"] = "12345678";
	response["mtu"] = "1500";
	response["verify"] = 0;
	response["band"] = 0;
	response["signal"] = 80;
	response["ip"] = "192.168.1.1";
	response["simStatus"] = 1;
	return AE_SYS_NOERROR;
}

int COrderNetwork::set4GParam(Json::Value &request, Json::Value &response)
{
	//AE_SET_4G_PARAM
	if (!response.isMember("enable") || !response["enable"].isInt()
		|| !response.isMember("apn") || !response["apn"].isString())
	{
		return AE_SYS_UNKNOWN_ERROR;
	}

	return AE_SYS_NOERROR;
}

int COrderNetwork::getNetworkSetting(Json::Value &request, Json::Value &response)
{
	//AE_GET_NETWORK_SETTING

	response["mobileData"] = 0;
	response["wifiShutdown"] = 0;
	response["wifiMode"] = 0;
	return AE_SYS_NOERROR;
}

int COrderNetwork::setNetworkSetting(Json::Value &request, Json::Value &response)
{
	//AE_SET_NETWORK_SETTING
	return AE_SYS_NOERROR;
}

}//Screen
