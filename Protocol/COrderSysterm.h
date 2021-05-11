#ifndef __CORDER_SYSTERM_H__
#define __CORDER_SYSTERM_H__

#include "IOrder.h"

namespace Screen
{
class COrderSysterm : public IOrder
{
public:
	enum
	{
	/*ϵͳ������*/
		AE_GET_ALL_CURRENT_SETTINGS = 1, /*��ȡ�������õĵ�ǰ����*/
		AE_GET_BATTERY_LEVEL = 2,		 /*��ȡ���״̬*/
		AE_GET_CAMERAS_STATUS = 3,		 /*��ȡ����ͨ�������¼��״̬*/
		AE_GET_GSENSOR_DATA = 4,		 /*��ȡ�豸G-sensor����*/
		AE_GET_GPS = 5,					 /*��ȡ��ǰGPS����*/
		AE_GET_DEVICE_INFO = 6,			 /*��ȡ�豸��Ϣ*/
		AE_GET_VEHICLE_INFO = 8,		 /*��ȡ���������Ϣ*/
		AE_SET_VEHICLE_INFO = 9,		 /*���ó��������Ϣ*/
		AE_GET_DRIVER_INFO = 10,		 /*��ȡ��ʻԱ�����Ϣ*/
		AE_SET_DRIVER_INFO = 11,		 /*���ü�ʻԱ�����Ϣ*/

		AE_GET_SATELLITE_INFO = 19, /*��ȡ�豸��ǰ��������Ϣ*/

		AE_GET_VEHICLE_STATUS = 26, /*��ȡ�豸״̬*/
		AE_GET_DEVICE_STATUS = 27, /*��ȡ����״̬*/

		AE_GET_PICTURE_SETTING = 186,  /*��ȡͼ������*/
		AE_SET_PICTURE_SETTING = 187,  /*����ͼ������*/
		AE_GET_COMPRESS_SETTING = 188, /*��ȡѹ������*/
		AE_SET_COMPRESS_SETTING = 189, /*����ѹ������*/

		AE_GET_IMAGE_SETTING = 190,	  /*��ȡͼƬ����*/
		AE_SET_IMAGE_SETTING = 191,	  /*����ͼƬ����*/
		AE_GET_GENERIC_SETTING = 192, /*��ȡͨ������*/
		AE_SET_GENERIC_SETTING = 193, /*����ͨ������*/
		AE_GET_PROMPT_SETTING = 194,  /*��ȡ��������*/
		AE_SET_PROMPT_SETTING = 195,  /*������������*/
		AE_GET_ALERT_SETTING = 196,	  /*��ȡ�澯����*/
		AE_SET_ALERT_SETTING = 197,	  /*���ø澯����*/
		AE_GET_SENSOR_SETTING = 198,  /*��ȡ��������*/
		AE_SET_SENSOR_SETTING = 199,  /*���ô�������*/
	};

	enum ErrCode
	{
		/*ϵͳ�������*/
		AE_SYS_NOERROR                          = 0,         /*����*/
		AE_SYS_UNKNOWN_ERROR                    = 1,         /*�����쳣���޷��ж�ԭ��*/
		AE_SYS_SESSION_START_FAIL               = 2,         /*��������ʧ��*/
		AE_SYS_INVALID_TOKEN                    = 3,         /*token����*/
		AE_SYS_REACH_MAX_CLINT                  = 4,         /*�ͻ����������ﵽ����*/
		AE_SYS_HDMI_INSERTED                    = 5,         /*APP����������ʱ��HDMI�˿���������������*/
		AE_SYS_NO_MORE_MEMORY                   = 6,         /*�豸�ڴ�ľ�*/
		AE_SYS_PIV_NOT_ALLOWED                  = 7,         /*��ǰ�ֱ��ʺ�֡�ʲ�֧����¼���ʱ��ץ��ͼƬ*/
		AE_SYS_SYSTEM_BUSY                      = 8,         /*ϵͳ��æ���޷�����ǰ����*/
		AE_SYS_NOT_READY                        = 9,         /*�豸��ʼ��δ���*/
		AE_SYS_RESET_FAILED                     = 10,        /*�豸��λʧ��*/
		AE_SYS_GET_FILE_LIST_FAILED             = 11,        /*��ȡ�ļ��б�ʧ��*/
		AE_SYS_UNACTIVED                        = 12,        /*�豸δ����*/
		AE_SYS_DEMO_MODE                        = 13,        /*�豸������ʾģʽ���޷����ò���*/
		AE_NO_BATTERY                           = 14,        /*�豸δװ�ص��*/
		AE_NO_TRAIN_INFO                        = 15,        /*δ�����ⲿ�豸*/
	};
public:
	COrderSysterm();
	~COrderSysterm();

	int getCameraStatus(Json::Value &request, Json::Value &response);
};



} //Screen
#endif //__CORDER_SYSTERM_H__
