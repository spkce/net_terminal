#ifndef __ADAPTER_H__
#define __ADAPTER_H__

#include "net_terminal.h"

using DevInfo_t = DEV_INFO_T;
using PtrDevInfo_t = DEV_INFO_T;
using AdptrFun_t = ADAPTER_T;
using PtrAdptrFun_t = ADAPTER_T;

class CAdapter
{
private:
	CAdapter();
	~CAdapter();
public:
	static CAdapter* instance();
	AdptrFun_t* getAdapter();
	bool getDeviceInfo(DevInfo_t* pdevInfo);

private:
	AdptrFun_t m_adapter;
};

#endif //__ADAPTER_H__

