
#include "ScreenProtocl.h"
#include "jsoncpp.h"

namespace Screen
{

class CNetProtocl: public IScreenProtocl
{
public:
	CNetProtocl();
	virtual ~CNetProtocl();

	virtual bool parse(char* buf, int len);
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
	Json::Value root;
	Json::CharReaderBuilder readerBuilder;

	std::unique_ptr<Json::CharReader> const jsonReader(readerBuilder.newCharReader());
	bool res = jsonReader->parse(recv.c_str(), recv.c_str() + recv.length(), &root, &errs);
	if (!res || !errs.empty())
	{
		return false;
	}
	//reader.parse(recv, root);

	return true;
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
