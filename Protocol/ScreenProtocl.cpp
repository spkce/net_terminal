
#include "ScreenProtocl.h"
#include "jsoncpp.h"
#include "openssl/aes.h"
#include "openssl/rand.h"
#include "openssl/evp.h"
#include "aes_encrypt.h"
namespace Screen
{

class CNetProtocl: public IScreenProtocl
{
public:
	CNetProtocl();
	virtual ~CNetProtocl();

	virtual bool parse(char* buf, int len);

	bool hub(Json::Value &request, Json::Value &response);

	bool start_session(Json::Value &request, Json::Value &response);
};

CNetProtocl::CNetProtocl()
{
}

CNetProtocl::~CNetProtocl()
{
}


bool CNetProtocl::parse(char* buf, int len)
{
	std::string recv = buf;
	Json::String errs;
	Json::Value request;
	Json::CharReaderBuilder readerBuilder;

	std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
	bool res = jsonReader->parse(recv.c_str(), recv.c_str() + recv.length(), &request, &errs);
	if (!res || !errs.empty())
	{
		return false;
	}
	
	if (request.isMember("token") && request.isMember("msg_id"))
	{
		Json::Value response;
		hub(request, response);
	}

	return true;
}

bool CNetProtocl::hub(Json::Value &request, Json::Value &response)
{
	if (!request.isMember("msg_id"))
	{
		return false;
	}
	printf("\033[35m""request = %s""\033[0m\n", request.toStyledString().c_str());
	unsigned int msgID = request["msg_id"].asUInt();

	switch(msgID)
	{
		case 257:
			start_session(request, response);
		break;
	}
	return true;
}

bool CNetProtocl::start_session(Json::Value &request, Json::Value &response)
{

	std::string rsaKey = request["rsaKey"].asString();

	response["rval"] = 0;
	response["msg_id"] = request["msg_id"].asUInt();
	response["param"] = 1;//TokenNumber
	response["version"] = 1;
	
	char sRsaEncodeKey[300] = {0};
 	char sKeyStr[100] = {0};
	unsigned char AesKey[16] = {0};
	RAND_pseudo_bytes(AesKey, 16);

	for (size_t i = 0; i < 16; i++)
	{
		sprintf(sKeyStr + i * 2, "%02x", AesKey[i]);
	}
	int iRet = app_rsa_encode(rsaKey.c_str(), sKeyStr, (unsigned char *)sRsaEncodeKey);

	response["aesCode"] = std::string(sRsaEncodeKey);

	response["timeout"] = 15;
	response["productType"] = 1;
}

IScreenProtocl * IScreenProtocl::getInstance()
{
	static CNetProtocl inst;
	return &inst;
}

IScreenProtocl::IScreenProtocl()
{

}

IScreenProtocl::~IScreenProtocl()
{

}

}//Screen
