#ifndef __ORDER_H__
#define __ORDER_H__

#include "jsoncpp.h"
namespace Screen
{

class IOrder
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

		AE_GET_DEVICE_STATUS = 26, /*��ȡ�豸״̬*/
		AE_GET_VEHICLE_STATUS = 27, /*��ȡ����״̬*/

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

		/*ý������*/
		AE_RECORD_START = 201,		 /*����¼��*/
		AE_RECORD_STOP = 202,		 /*�ر�¼��*/
		AE_EVENT_RECORD_START = 203, /*��������¼��*/
		AE_AUDIO_RECORD_START = 204, /*������Ƶ¼��*/
		AE_AUDIO_RECORD_STOP = 205,	 /*�ر���Ƶ¼��*/

		/*����ӿ�������*/
		AE_WIFI_RESTART = 301,		  /*����wifi*/
		AE_GET_STA_PARAM = 302,		  /*��ȡSTA����*/
		AE_SET_STA_PARAM = 303,		  /*����STA����*/
		AE_GET_AP_PARAM = 304,		  /*��ȡAP����*/
		AE_SET_AP_PARAM = 305,		  /*����AP����*/
		AE_GET_4G_PARAM = 306,		  /*��ȡ4G����*/
		AE_SET_4G_PARAM = 307,		  /*����4G����*/
		AE_GET_NETWORK_SETTING = 398, /*��ȡ��������*/
		AE_SET_NETWORK_SETTING = 399, /*������������*/

		/*�洢������*/
		AE_GET_SD_LETTER = 401,			/*��ȡ�Ѳ����̷�*/
		AE_GET_SD_INFO = 402,			/*��ȡSD��Ϣ*/
		AE_SET_SD_LOCK_STATUS = 403,	/*����SD��״̬*/
		AE_SET_SD_PASSWD = 404,			/*����SD����*/
		AE_FORMAT = 405,				/*��ʽ��SD��*/
		AE_GET_RECORD_SCHEDILE = 406,	/*��ȡ¼��ƻ�*/
		AE_SET_RECORD_SCHEDILE = 407,	/*����¼��ƻ�*/
		AE_COPY_DAY_SCHEDILE = 408,		/*����һ���¼��ƻ�*/
		AE_COPY_CHANNEL_SCHEDILE = 409, /*����һ��ͨ����¼��ƻ�*/
		AE_EXPORT_MEDIA_FILE = 410,		/*�豸ý���ļ��������ⲿ�洢�豸*/
		AE_EXPORT_LOG = 411,			/*�豸��־�������ⲿ�洢�豸*/
		AE_EXPORT_CONFIG = 414,			/*���豸�е������ļ����뵽�ⲿ�豸*/
		AE_IMPORT_CONFIG = 415,			/*���ⲿ�豸�е������ļ����뵽�豸*/
		AE_CONCEL_EXPORT = 416,			/*ȡ���ļ�����*/
		AE_GET_STORAGE_SETTING = 498,	/*��ȡ�洢����*/
		AE_SET_STORAGE_SETTING = 499,	/*���ô洢����*/
		/*ʱ��������*/
		AE_GET_DAYLIGHT_TIME = 501, /*��ȡ����ʱ*/
		AE_SET_DAYLIGHT_TIME = 502, /*��������ʱ*/
		AE_GET_TIMEZONE = 503,		/*��ȡʱ��*/
		AE_SET_TIMEZONE = 504,		/*����ʱ��*/
		AE_GET_TIME_SETTING = 598,	/*��ȡʱ������*/
		AE_SET_TIME_SETTING = 599,	/*����ʱ������*/

		/*֪ͨ������*/
		AE_NOTIFICATION = 601, /*֪ͨ����Ϣ*/

		/*ƽ̨����������*/
		AE_GET_PLATFORM_CONN_INFO = 701,	/*��ȡƽ̨��Ϣ*/
		AE_SET_PLATFORM_CONN_INFO = 702,	/*����ƽ̨��Ϣ*/
		AE_GET_808_CONN_INFO = 703,			/*��ȡ808������Ϣ*/
		AE_SET_808_CONN_INFO = 704,			/*����808������Ϣ*/
		AE_GET_808_CONN_INFO_2 = 705,		/*��ȡ808_2������Ϣ*/
		AE_SET_808_CONN_INFO_2 = 706,		/*����808_2������Ϣ*/
		AE_GET_OPERATE_PLATFORM_INFO = 707, /*��ȡ��άƽ̨������Ϣ*/
		AE_SET_OPERATE_PLATFORM_INFO = 708, /*������άƽ̨������Ϣ*/
		AE_GET_NTP_PLATFORM_INFO = 709,		/*��ȡNTPƽ̨������Ϣ*/
		AE_SET_NTP_PLATFORM_INFO = 710,		/*����NTPƽ̨������Ϣ*/

		/*��������*/
		AE_GET_FACE_INFO = 922,				   /*��ȡ�豸�洢��������Ϣ*/
		AE_SET_FACE_INFO = 923,				   /*�����豸�洢��������Ϣ*/
		AE_GET_OVERTIME_DRIVING_SETTING = 924, /*���ڻ�ȡ��ʱ���ʻʱ��β���*/
		AE_SET_OVERTIME_DRIVING_SETTING = 925, /*�������ó�ʱ���ʻʱ��β���*/
		AE_FACE_CONTRAST = 932,					/*�����ȶԽ��*/

		/*IPC����*/
		AE_GET_ADDED_IPC_LIST = 1001,	/*��ȡ�Ѿ���ӵ�ipc�б�*/
		AE_GET_ADDABLE_IPC_LIST = 1002, /*��ȡ���ߵ�ipc�б�*/
		AE_ADD_IPC = 1003,				/*�������IPC*/
		AE_DEL_IPC = 1004,				/*ɾ��IPC*/
		AE_GET_PERIPHERAL_STATUS = 1008, /*��ȡ����״̬*/

		/*�豸����������*/
		AE_CAPABILITY_GET = 1901,			   /*��ȡ����������*/
		AE_CAPABILITY_IMAGE_GET = 1911,		   /*��ȡͼ��������*/
		AE_CAPABILITY_BASIC_GET = 1921,		   /*��ȡ����������*/
		AE_CAPABILITY_NETWORK_GET = 1931,	   /*��ȡ����������*/
		AE_CAPABILITY_STORAGE_GET = 1941,	   /*��ȡ�洢������*/
		AE_CAPABILITY_INTELLIGENCE_GET = 1951, /*��ȡ���ܼ�ʻ����������*/
		AE_CAPABILITY_PROMPT_GET = 1952,	   /*��ȡ����������*/
		AE_CAPABILITY_ALERT_GET = 1953,		   /*��ȡ�澯������*/
		AE_CAPABILITY_SENSOR_GET = 1954,	   /*��ȡ����������*/
		AE_CAPABILITY_ADAS_GET = 1955,		   /*��ȡADAS������*/
		AE_CAPABILITY_DBA_GET = 1956,		   /*��ȡDBA������*/
		AE_CAPABILITY_VSD_GET = 1957,		   /*��ȡVSD������, �����ã�����������DBA*/
		AE_CAPABILITY_BSD_GET = 1958,		   /*��ȡBSD������*/

		AE_CAPABILITY_FACE_GET = 1959, /*��ȡ����ʶ��������*/

		AE_CAPABILITY_TIME_GET = 1961, /*��ȡʱ��������*/

		AE_CAPABILITY_WHD_GET = 1962, /*��ȡWHD������*/

		AE_CAPABILITY_PICTURE_GET = 1971,	/*��ȡͼƬ������*/
		AE_CAPABILITY_COMPRESS_GET = 1981,	/*��ȡѹ��������*/
		AE_CAPABILITY_BLUETOOTH_GET = 1991, /*��ȡ����������*/
		AE_CAPABILITY_IPC_GET = 1993,		/*ipc������*/

		/*����������*/
		AE_GET_ADAS_SETTING = 901,			   /*��ȡADAS����*/
		AE_SET_ADAS_SETTING = 902,			   /*����ADAS����*/
		AE_GET_ADAS_CALIBRATION = 903,		   /*��ȡADAS�궨*/
		AE_SET_ADAS_CALIBRATION = 904,		   /*����ADAS�궨*/
		AE_GET_DBA_SETTING = 905,			   /*��ȡDBA����*/
		AE_SET_DBA_SETTING = 906,			   /*����DBA����*/
		AE_ENTER_SPEED_CALIBRATION = 907,	   /*�����ٶȱ궨*/
		AE_EXIT_SPEED_CALIBRATION = 908,	   /*�뿪�ٶȱ궨*/
		AE_START_SPEED_CALIBRATION = 909,	   /*��ʼ�ٶȱ궨*/
		AE_GET_SPEED_CALIBRATION_STATUS = 910, /*��ȡ�ٶȱ궨״̬*/
		AE_GET_CAR_STATUS = 911,			   /*��ȡ����״̬*/
		AE_GET_VSD_SETTING = 912,			   /*��ȡVSD����*/
		AE_SET_VSD_SETTING = 913,			   /*����VSD����*/
		AE_START_ADAS_CALIBRATION = 914,	   /*��ʼADAS����궨*/
		AE_GET_SPEED_CALIBRATION = 915,		   /*��ȡ�ٶȱ궨*/
		AE_SET_SPEED_CALIBRATION = 916,		   /*�����ٶȱ궨*/
		AE_TURN_CALIBRATION = 917,			   /*ת��궨*/
		AE_BREAK_CALIBRATION = 918,			   /*ɲ���궨*/
		AE_GET_SPEED = 919,					   /*��ȡ����*/
		AE_GET_BSD_SETTING = 920,			   /*��ȡBSD����*/
		AE_SET_BSD_SETTING = 921,			   /*����BSD����*/
		AE_GET_IO_WARN_INFO = 928,			   /*��ȡIO��������*/
		AE_SET_IO_WARN_INFO = 929,			   /*����IO����ͨ������*/
		AE_GET_PULSE_SETTING = 930,			   /*��ȡ��������*/
		AE_SET_PULSE_SETTING = 931,			   /*�����������*/
		AE_GET_IO_OUTPUT_SETTING = 934,		   /*��ȡIO�������*/
		AE_SET_IO_OUTPUT_SETTING = 935,		   /*����IO�������*/

		AE_GET_WHD_SETTING = 938, /*��ȡWHD����*/
		AE_SET_WHD_SETTING = 939, /*����WHD����*/
		AE_SET_PFS_INFO = 940,	  /*��ȡʵʱ������Ϣ*/

		AE_GET_CUSTOM_SMART_CHAN_INFO = 941, /*��ȡ�û��Զ�����������ͷ��Ϣ*/
		AE_SET_CUSTOM_SMART_CHAN_INFO = 942, /*�����û��Զ�����������ͷ��Ϣ*/

		/* �¼������� */
		AE_GET_EVENT_DISPLAY_SETTING = 950, /* ��ȡ�¼���ʾ */
		AE_SET_EVENT_DISPLAY_SETTING = 951,
		/*���̿���������*/
		AE_START_SESSION = 257,       /*����*/
		AE_STOP_SESSION = 258,       /*�Ͽ�*/
		/*ϵͳ������*/
		AE_CHECK_SELF = 2200,	 /*�Լ�����*/
		AE_RESET_DEFAULT = 2201,	 /*�ָ�Ĭ�ϲ���*/
		AE_REBOOT_SYSTEM = 2202,	 /*����ϵͳ*/
		AE_SHUTDOWN_SYSTEM = 2203,	 /*�ػ�*/
		AE_UPGRADE = 2204,			 /*����*/
		AE_GET_SETTING = 2205,		 /*��ȡĳ�����õĵ�ǰ����*/
		AE_SET_SETTING = 2206,		 /*����ĳ�����õĵ�ǰ����*/
		AE_GET_UPGRADE_PATH = 2207,	 /*��ȡ����·��*/
		AE_GET_ACTIVE_STATUS = 2208, /*��ȡ�豸����״̬*/
		AE_GET_CHANNEL_INFO = 2209,	 /*��ȡOSDͨ����Ϣ*/
		AE_SET_CHANNEL_INFO = 2210,	 /*����OSDͨ����Ϣ*/
		AE_APK_UPGRADE = 2211,		 /*��������׿*/
		AE_STARTUP_SYSTEM = 2212,	 /*��������*/
		AE_DOWNLOAD = 2213,			 /*����*/
		AE_GET_LICENSE_INFO = 2219,	/*��ȡ���֤��Ϣ*/
		AE_START_SELF_CHECKING = 2220,	/*�豸�����Լ�*/
		AE_GET_AREA_INFO = 2221,	/*��ȡ����Χ����Ϣ*/

		/*�ļ�������*/
		AE_GET_VIDEO_FILE_LIST = 2301,		   /*��ȡ¼���ļ��б�*/
		AE_GET_IMAGE_FILE_LIST = 2302,		   /*��ȡͼ���ļ��б�*/
		AE_GET_AUDIO_FILE_LIST = 2303,		   /*��ȡ��Ƶ�ļ��б�*/
		AE_DELETE_FILE = 2304,				   /*ɾ���ļ�*/
		AE_GET_TOTAL_NUM = 2305,			   /*��ȡ���ļ���Ŀ*/
		AE_GET_RECORD_STATUS_BY_MONTH = 2306,  /*��ȡ����ÿ���¼��״̬*/
		AE_LOCK_FILE = 2307,				   /*�ļ�����*/
		AE_UNLOCK_FILE = 2308,				   /*�ļ�����*/
		AE_GET_VIDEO_TIMETAMP = 2309,		   /*��ȡ¼��ʼʱ��㼰����ʱ���*/
		AE_GET_VIDEO_FILE_LIST_BY_TIME = 2310, /*��ȡĳһ���¼��ʱ���*/
		AE_GET_RECORD_DAYS = 2311,			   /*��ȡ��ǰ�豸����¼�������*/

		/*͸��������*/
		AE_GET_CUSTOM = 2401, /*��ȡ�Զ�������*/ 
		AE_SET_CUSTOM = 2402, /*�����Զ�������*/

		/*ý��������*/
		AE_START_PREVIEW = 2501,		  /*��ʼԤ��*/
		AE_STOP_PREVIEW = 2502,			  /*ֹͣԤ��*/
		AE_START_PLAYBACK = 2503,		  /*��ʼ�ط�*/
		AE_STOP_PLAYBACK = 2504,		  /*ֹͣ�ط�*/
		AE_START_AUDIO = 2505,			  /*��ʼ��Ƶ�ط�*/
		AE_STOP_AUDIO = 2506,			  /*ֹͣ��Ƶ�ط�*/
		AE_TAKE_PHOTO = 2507,			  /*ץͼ*/
		AE_SET_RECORD_LOCK_STATUS = 2508, /*����¼������״̬*/
		AE_GET_RTSP_INFO = 2509,		  /*��ȡRTSP�û���������*/

		/*��Ϣ�����*/
		AE_SEND_APP_INFO = 2704,		  /*app���豸������Ϣ*/
		AE_SEND_TOUCH_INFO = 2705,		/*app���豸���ʹ�����Ϣ*/
		AE_SEND_UI_STATUS = 2706,		/*app���豸���ͽ���״̬*/

		AE_SEND_AREA_INFO = 2804,		/*�豸��app����������Ϣ*/
		AE_CLEAR_ALL_AREA_INFO = 2805,	/*�豸��app�������Χ��ָ��*/
		AE_GET_APP_INFO = 2806,		/*�豸��app��ѯ�汾��Ϣ*/
		AE_SEND_WARN_INFO = 2807,		/*�豸��app����BSD������Ϣ*/
		AE_SEND_SELF_CHECKING_INFO = 2808,		/*�豸��app�����Լ���Ϣ*/
		AE_SEND_PARAMETER = 2809,		/*�豸��app���Ͳ���*/


		AE_CAPABILITY_CALIBRATION_GET = 4101, /*��ȡ�궨����*/

		/*��������*/
		AE_FACTORY = 5001, /*��������*/
	};

	enum
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

	/*Э���������*/
	enum
	{
		AE_PROT_JSON_PACKAGE_ERROR              =301,       /*json�ַ�����֧��Ƕ��*/
		AE_PROT_JSON_PACKAGE_TIMEOUT            =302,       /*5����δ�յ�json������־*/
		AE_PROT_JSON_SYNTAX_ERROR               =303,       /*json�ַ����ļ�ֵ�԰����﷨����*/
		AE_PROT_INVALID_OPTION_VALUE            =304,       /*AE_SET_SETTING�����json�ַ����а�����֧�ֵ�ѡ��*/
		AE_PROT_INVALID_OPERATION               =305,       /*��֧�ֵ������*/
		AE_PROT_INVALID_TYPE                    =306,       /*Э�������type�Ƿ�*/
		AE_PROT_INVALID_PARAM                   =307,       /*Э�������param�Ƿ�*/
		AE_PROT_INVALID_PATH                    =308,       /*������ļ���Ŀ¼������*/
		AE_TIMEZONE_INTERVAL_ERROR              =309,       /*����ʱ���С��30��*/
		AE_TIMEZONE_WEEK_ERROR                  =310,       /*����ʱ���ڴ���*/
		AE_TIMEZONE_DAY_ERROR                   =311,       /*����ʱ���ڴ���*/
		AE_VOLTAGE_ERROR						=312,		/*����ʧ�ܣ���ǰ��ѹС�����õ�ѹ*/
		AE_VOLTAGE_NOT_CONNECTED				=313,		/*����ʧ�ܣ�δ���ӽ�ѹ��*/
		AE_SET_VALUE_TOO_LOW				    =314,		/*���ò�������*/
		AE_SET_VALUE_TOO_HIGH				    =314,		/*���ò�������*/
	};
	/**
	* @brief ��Ϣ�ַ�
	* @param msgID ��ϢID
	* @param request ������
	* @param response �ظ�
	* @return �ɹ�/ʧ��
	**/
	static bool orderHub(unsigned int msgID, Json::Value &request, Json::Value &response);
	/**
	* @brief ֪ͨ��Ϣ��װ
	* @param msgID ��ϢID
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	* @return �ɹ�/ʧ��
	**/
	static bool notifyHub(unsigned int msgID, char* buf, int len, Json::Value &send);
protected:
	/**
	* @brief �����������趨protectedȨ�ޣ�����ʵ�����ɼ̳�
	**/
	virtual ~IOrder() {};
};

}//Screen

#endif //__ORDER_H__
