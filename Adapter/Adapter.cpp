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
	if (m_adapter.device_info_get == NULL || pdevInfo == NULL)
	{
		return false;
	}
	return m_adapter.device_info_get(pdevInfo) == 0;
}

bool CAdapter::getDeviceStatus(DevStatus_t* pdevStatus)
{
	if (m_adapter.device_status_get == NULL || pdevStatus == NULL)
	{
		return false;
	}
	return m_adapter.device_status_get(pdevStatus) == 0;
}

bool CAdapter::getVehicleStatus(VehStatus_t* pVehStatus)
{
	if (m_adapter.vehicle_status_get == NULL || pVehStatus == NULL)
	{
		return false;
	}
	return m_adapter.vehicle_status_get(pVehStatus) == 0;
}

bool CAdapter::getSetting(Setting_t* pstSetting)
{
	if (m_adapter.setting_get == NULL || pstSetting == NULL)
	{
		return false;
	}
	return m_adapter.setting_get(pstSetting) == 0;
}

bool CAdapter::sendTouchInfo(TouchInfo_t* pstTouchInfo)
{
	if (m_adapter.send_touch_info == NULL || pstTouchInfo == NULL)
	{
		return false;
	}
	return m_adapter.send_touch_info(pstTouchInfo) == 0;
}

