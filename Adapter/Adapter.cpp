#include "Adapter.h"
#include "stdio.h"

CAdapter::CAdapter()
{

}

CAdapter::~CAdapter()
{
	
}

CAdapter* CAdapter::instance()
{
	static CAdapter _inst;
	return &_inst;
}

PADAPTER_T CAdapter::getAdapter()
{
	return &m_adapter;
}

bool CAdapter::getDeviceInfo(PDEV_INFO_T pdevInfo)
{
	if (m_adapter.device_info_get == NULL)
	{
		return false;
	}

	m_adapter.device_info_get(pdevInfo);

	return true;
}