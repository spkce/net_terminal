#ifndef __ORDER_SYSTERM_H__
#define __ORDER_SYSTERM_H__

#include "Order.h"

namespace Screen
{

class COrderSysterm : public IOrder
{
public:
	/**
	* @brief ��������
	**/
	virtual ~COrderSysterm() {};
	/**
	* @brief ��ȡ�������õĵ�ǰ����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getDeviceSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ���״̬
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getBatteryLevel(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ����ͨ�������¼��״̬
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getCameraStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ�豸G-sensor����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getGSensorData(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ��ǰGPS����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getGPSData(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ�豸��Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getDeviceInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ���������Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getVehicleInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ���ó��������Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setVehicleInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ��ʻԱ�����Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getDriverInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ���ü�ʻԱ�����Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setDriverInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ����״̬
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getCarStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ�豸��ǰ��������Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getSatelliteInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ�豸״̬
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getDeviceStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ����״̬
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getVehicleStatus(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡͼ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getPictureSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ����ͼ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setPictureSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡѹ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getCompressSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ����ѹ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setCompressSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡѹ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getImageSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ����ͼƬ����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setImageSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡͨ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getGenericSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ����ͨ������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setGenericSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ��������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getPromptSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ������������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setPromptSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ�澯����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getAlertSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ���ø澯����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setAlertSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡĳ�����õĵ�ǰ����
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getStting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ��������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getSensorSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ���ô�������
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int setSensorSetting(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ���֤��Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getLicenseInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief �豸�����Լ�
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int startSelfChecking(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ����Χ����Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int getAreaInfo(Json::Value &request, Json::Value &response);
	/**
	* @brief ��ȡ����Χ����Ϣ
	* @param request ������
	* @param response �ظ�����
	* @return ������
	**/
	static int checkSelf(Json::Value &request, Json::Value &response);

};

}//Screen

#endif	//__ORDER_SYSTERM_H__
