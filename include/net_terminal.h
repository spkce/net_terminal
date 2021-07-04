#ifndef __NET_TERMINAL_H__
#define __NET_TERMINAL_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define NET_APP_DEV_INFO_LEN 16
#define NET_APP_VERSION_LEN 32
#define NET_APP_DATE_LEN 24      /*ʱ�䣬ʱ���ַ�����󳤶�*/
#define FACE_NAME_LEN 20
#define FACE_IDENTITY_LEN 32
#define FACE_LICENSE_LEN 32
#define CONTENT_MAX_LEN 64
#define PATH_MAX_LEN 128           /*·����󳤶�*/
#define CAM_MAX 8

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
	char curTime[NET_APP_DATE_LEN];/*�豸ʱ��*/

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

typedef struct tagPeriStatus
{
	int lift;/*����������״̬*/
	int carry;/*�ܱմ�����״̬*/
	int hermetic;/*���ش�����״̬*/
	int led;/*LED��״̬*/
	int audioAlarm;/*���ⱨ����״̬*/
	int conbox;/*can����״̬*/
	int cam[CAM_MAX];/*����ͷ״̬*/
}PERI_STATUS_T, *PPERI_STATUS_T;

typedef struct tagCarStatus
{
	int corneringLamp;	/*ת��� ״̬*/
	int brake;			/*ɲ�� ״̬*/
}CAR_STA_T, *PCAR_STA_T;

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

typedef struct tagMsghdr
{
	unsigned int msgID;
}MSG_HDR_T, *PMSG_HDR_T;

typedef struct tagWarnInfo
{
	int type;
}WARN_INFO_T, *PWARN_INFO_T;

typedef struct tagFaceInfo
{
	int faceID;
	char name[FACE_NAME_LEN];
	char identityID[FACE_IDENTITY_LEN];
	char path[PATH_MAX_LEN];
	char license[FACE_LICENSE_LEN];
}FACE_INFO_T, *PFACE_INFO_T;

typedef struct tagADASAlarm
{
	int detailType;
	int channel;
	int result;
	char picName[PATH_MAX_LEN];
	char vIdeoName[PATH_MAX_LEN];
	
}ADAS_INFO_T,PADAS_INFO_T;
typedef struct tagPhotoTaken
{
	int type;
	int channel;
	int filesize;
	int result;
	char path[PATH_MAX_LEN];
	char thmPath[PATH_MAX_LEN];
	char startTime[NET_APP_DATE_LEN];
}PHOTO_TAKEN_T,PPHOTO_TAKEN_T;

typedef struct tagNotification
{
	char type[32];
	union {
		ADAS_INFO_T adasAlarm;
		PHOTO_TAKEN_T photoTaken;
	};
}NOTIFICATION_T, *PNOTIFICATION_T;

typedef struct tagMsgInfo
{
	int msgType;
	int showType;
	int durction;
	int priority;
	char message[CONTENT_MAX_LEN];
}MESSAGE_INFO_T, *PMESSAGE_INFO_T;

typedef struct tagcheckSelfInfo
{
	int checkCount;
	int index;
	int result;
	char content[CONTENT_MAX_LEN];
}CHECk_INFO_T, *PCHECk_INFO_T;

/*�ⲿ�ӿں���*/
typedef struct tagAdapterFunc
{
	int (*device_info_get)(PDEV_INFO_T pstDevInfo);
	int (*device_status_get)(PDEV_STATUS_T pstDevStatus);
	int (*vehicle_status_get)(PVEH_STATUS_T pstVehStatus);
	int (*peripheral_status_get)(PPERI_STATUS_T pstPeriStatus);
	int (*car_status_get)(PCAR_STA_T pstSetting);
	int (*setting_get)(PSETTING_T pstSetting);
	int (*send_touch_info)(PTOUCH_INFO_T pstSetting);
	int (*get_face_total_number)(void);
	int (*get_face_info)(unsigned int index, PFACE_INFO_T pInfo);
	int (*set_face_info)(int index, PFACE_INFO_T pInfo);
	int (*take_photo)(int channel, int type);
	int (*checkSelf)(void);
}ADAPTER_T, *PADAPTER_T;


/**
 * @brief ��ʼ����׿��
 */
void net_termianl_init();

/**
 * @brief ��ȡ������ָ��
 * @return ������ָ��
 */
PADAPTER_T net_terminal_adapter_get();

/**
 * @brief ��Ϣ����
 * @param buf ��Ϣ������ 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_notify(char* buf, int len);

/**
 * @brief GPS��������
 * @param buf GPS���ݻ����� 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_pushGPS(char* buf, int len);

#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
