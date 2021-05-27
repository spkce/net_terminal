#ifndef __NET_TERMINAL_H__
#define __NET_TERMINAL_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define NET_APP_DEV_INFO_LEN 16
#define NET_APP_VERSION_LEN 32
#define NET_APP_DATE_LEN 24      /*ʱ�䣬ʱ���ַ�����󳤶�*/

/**
 * @brief ��ȡ�豸��Ϣ
 */

typedef struct tagDevInfo
{
    unsigned int uDDR;
    unsigned int uLanguage;
    char  sDeviceType[NET_APP_DEV_INFO_LEN];/*�豸�ͺţ�AE-CN2213-C1*/
    char  sFirmVersion[NET_APP_DEV_INFO_LEN];/*�̼��汾��V1.1.0*/
    char  sFirmDate[NET_APP_DEV_INFO_LEN];/*�̼����ڣ�2016.04.15*/
    char  sParamVersion[NET_APP_DEV_INFO_LEN];/*�����汾��V1.2.0*/
    char  sSerialNum[NET_APP_DEV_INFO_LEN];/*���кţ�585022848*/
    char  sVerifyCode[NET_APP_DEV_INFO_LEN];/*�豸��֤�룬HNDAGK*/
    char  sCustomID[NET_APP_DEV_INFO_LEN];/*���Ƶ���*/
    char  sHardwareVer[NET_APP_DEV_INFO_LEN];/*Ӳ���汾��V1.1.0*/
    char  sMCUVer[NET_APP_VERSION_LEN];/*MCU�汾��*/
    char  sDspVer[NET_APP_VERSION_LEN];/*DSP�汾��*/
    char  sFpgaVer[NET_APP_VERSION_LEN];/*FPGA�汾��*/
	char  sGpsVer[NET_APP_VERSION_LEN];/*GPS�汾��*/
}DEV_INFO_T, *PDEV_INFO_T;

typedef struct tagDevStatus
{
	int accStatus;/*acc ״̬*/
	int CSQ;/*GSM�ź�ǿ��*/
	int locationStatus; /*��λ״̬*/
	int bizPIfLoginStatus; /*ҵ��ƽ̨��¼״̬*/
	char  curTime[NET_APP_DATE_LEN];/*�豸ʱ��*/

}DEV_STATUS_T, *PDEV_STATUS_T;

typedef struct tagVehStatus
{
	int feedProtection; /*acc ״̬*/
	int gear;/*��λ*/
 	int carryStatus;/*�ػ�״̬*/
	int hermeticStatus;/*�ܱ�״̬*/
	int liftStatus;/*����״̬*/
	int speedLimitStatus;/*����״̬*/
	int liftLimitStatus;/*�޾�״̬*/
	int rotateLimitStatus;/*��ת״̬*/
	int lockStatus;/*����״̬*/
	int maintainMode;/*ά��ģʽ*/
	int speedLimitThreshold;/*������ֵ*/
}VEH_STATUS_T, *PVEH_STATUS_T;

typedef struct tagSetting
{
	char sTime[NET_APP_DATE_LEN];/*ʱ�䣬Ŀǰֻ֧��ʱ��Ļ�ȡ*/
}SETTING_T, *PSETTING_T;

typedef struct tagTouchInfo
{
	int touchX;/*X����*/
	int touchY;/*Y����*/
	int screenWidth;/*��Ļ��*/
	int screenHeight;/*��Ļ��*/
	int touchType;/*�������ͣ�0�ͷţ�1����*/
}TOUCH_INFO_T, *PTOUCH_INFO_T;


/*�ⲿ�ӿں���*/
typedef struct tagAdapterFunc
{
	int (*device_info_get)(PDEV_INFO_T pstDevInfo);
	int (*device_status_get)(PDEV_STATUS_T pstDevStatus);
	int (*vehicle_status_get)(PVEH_STATUS_T pstVehStatus);
	int (*setting_get)(PSETTING_T pstSetting);
	int (*send_touch_info)(PTOUCH_INFO_T pstSetting);
}ADAPTER_T, *PADAPTER_T;



void net_termianl_init();

PADAPTER_T net_terminal_adapter_get();


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
