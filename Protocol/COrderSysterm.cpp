

#include "COrderSysterm.h"

namespace Screen
{

COrderSysterm::COrderSysterm()
{
}

COrderSysterm::~COrderSysterm()
{
}

int COrderSysterm::getCameraStatus(Json::Value &request, Json::Value &response)
{
	Json::Value &resParam = response["param"];
	for (int i = 0; i < 6; i++)
	{
		resParam[i]["chanNo"] = i;
		resParam[i]["connStat"] = 0;
		resParam[i]["recordStatus"] = 0;
		resParam[i]["subRecStatus"] = 0;
		char name[12] = {0};
		snprintf(name, sizeof(name), "CH%d", i + 1);
		resParam[i]["name"] = std::string(name);
	}

	response["rval"] = 0u;
	response["msgId"] = request["msgId"].asUInt();
	response["token"] = request["token"].asUInt();
	return AE_SYS_NOERROR;
}

} //Screen
