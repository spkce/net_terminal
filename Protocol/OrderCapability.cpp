#include "OrderCapability.h"

namespace Screen
{

int COrderCapability::getCapability(Json::Value &request, Json::Value &response)
{
	//AE_CAPABILITY_GET
	//if (!request.isMember("chanNo") || !request["chanNo"].isString())
	//{
	//	return AE_SYS_UNKNOWN_ERROR;
	//}
	
	response["generic"] = 1;
	response["image"] = 1;
	response["network"] = 1;
	response["storage"] = 1;
	response["interlliDrive"] = 1;
	response["time"] = 1;
	response["picture"] = 1;
	response["compress"] = 1;
	response["bluetooth"] = 1;
	response["peripheral"] = 1;
	response["calibration"] = 1;
	return AE_SYS_NOERROR;
}

int COrderCapability::getCapabilityImage(Json::Value &request, Json::Value &response)
{
	//AE_CAPABILITY_IMAGE_GET
	response["resolution"] = 1;
	return AE_SYS_NOERROR;
}

int COrderCapability::getCapabilityBasic(Json::Value &request, Json::Value &response)
{
	//AE_CAPABILITY_BASIC_GET
	response["chanNum"] = 6;
	response["voiceChanNum"] = 1;
	response["streamNum"] = 6;
	response["cfgChan"][0] = 1;
	response["cfgChan"][1] = 2;
	response["mainStreamPreview"][0] = 0;
	response["mainStreamPreview"][1] = 1;
	response["mainStreamRecord"][0] = 0;
	response["mainStreamRecord"][1] = 1;
	response["subStreamPreview"][0] = 0;
	response["subStreamPreview"][1] = 1;
	response["subStreamRecord"][0] = 0;
	response["subStreamRecord"][1] = 1;
	response["language"] = 0;
	response["LCDRotate"] = 0;
	response["shutdownDelay"] = 300;
	response["shutdownDelayCustom"]["min"] = 10;
	response["shutdownDelayCustom"]["max"] = 1000;
	response["plateNumber"]["min"] = 4;
	response["plateNumber"]["max"] = 4;
	response["remoteUpgrade"] = 1;
	return AE_SYS_NOERROR;
}

int COrderCapability::getCapabilityNetwork(Json::Value &request, Json::Value &response)
{
	//AE_CAPABILITY_NETWORK_GET
	return AE_SYS_NOERROR;
}


} //Screen
