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

bool CAdapter::getPeripheralStatus(PeriStatus_t* pPeriStatus)
{
	if (m_adapter.peripheral_status_get == NULL || pPeriStatus == NULL)
	{
		return false;
	}
	return m_adapter.peripheral_status_get(pPeriStatus) == 0;
}

bool CAdapter::getCarStatus(CarStatus_t* pCarStatus)
{
	if (m_adapter.car_status_get == NULL || pCarStatus == NULL)
	{
		return false;
	}

	return m_adapter.car_status_get(pCarStatus) == 0;
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

int CAdapter::getFaceNum()
{
	if (m_adapter.get_face_total_number == NULL)
	{
		return 0;
	}
	return m_adapter.get_face_total_number();
}

bool CAdapter::getFaceInfo(int index, FaceInfo_t* pInfo)
{
	if (m_adapter.get_face_info == NULL || pInfo == NULL)
	{
		return false;
	}
	return m_adapter.get_face_info(index, pInfo) == 0;
}

bool CAdapter::setFaceInfo(int index, FaceInfo_t* pInfo)
{
	if (m_adapter.set_face_info == NULL)
	{
		return false;
	}
	return m_adapter.set_face_info(index, pInfo) == 0;
}

bool CAdapter::faceContrast(const char* pic)
{
	if (m_adapter.faceContrast == NULL)
	{
		return false;
	}
	return m_adapter.faceContrast(pic) == 0;
}

bool CAdapter::takePhoto(int channel, int type)
{
	if (m_adapter.take_photo == NULL)
	{
		return false;
	}
	return m_adapter.take_photo(channel, type) == 0;
}

bool CAdapter::checkSelf()
{
	if (m_adapter.checkSelf == NULL)
	{
		return false;
	}
	return m_adapter.checkSelf() == 0;
}

int CAdapter::getCeritfyNum()
{
	if (m_adapter.get_ceritfy_Num == NULL)
	{
		return 0;
	}

	return m_adapter.get_ceritfy_Num();
}

bool CAdapter::getCeritfy(unsigned int id, Ceritfy_t* pCeritfy)
{
	if (m_adapter.get_ceritfy == NULL || pCeritfy == NULL)
	{
		return false;
	}

	return m_adapter.get_ceritfy(id, pCeritfy) == 0;
}
int CAdapter::getAreaNum()
{
	if (m_adapter.get_area_Num == NULL)
	{
		return 0;
	}

	return m_adapter.get_area_Num();
}

bool CAdapter::getArea(unsigned int id, Area_t* pArea)
{
	if (m_adapter.get_area == NULL || pArea == NULL)
	{
		return false;
	}

	return m_adapter.get_area(id, pArea) == 0;
}

bool CAdapter::upgradeResult(unsigned int result, unsigned int progress)
{
	if (m_adapter.upgrade_result == NULL)
	{
		return false;
	}

	return m_adapter.upgrade_result(result, progress) == 0;
}

void* CAdapter::getFileList(unsigned int type, FileCriteria_t* pCriteria, unsigned int* pNum)
{
	if (m_adapter.file_list_get == NULL || pCriteria == NULL || pNum == NULL)
	{
		return NULL;
	}

	return m_adapter.file_list_get(type, pCriteria, pNum);
}

bool CAdapter::searchFileNext(int reverse, void *pHandle, FileInfo_t* pFileInfo)
{
	if (m_adapter.search_file_next == NULL || pHandle == NULL || pFileInfo == NULL)
	{
		return false;
	}

	return m_adapter.search_file_next(reverse, pHandle, pFileInfo) == 0;
}
