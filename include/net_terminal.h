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
#define CERTIFY_MAX_LEN 256
#define MAX_POLYGON_VERTEX_NUM 30		/*������ζ�����Ŀ*/
#define MAX_INFLECTION_POINT_NUM 50		/*���յ���Ŀ*/
#define MAX_AREA_NUM 50					/*���������Ŀ*/
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
	int faceID;							/*����ID*/
	char name[FACE_NAME_LEN];			/*����*/
	char identityID[FACE_IDENTITY_LEN];	/*���֤*/
	char path[PATH_MAX_LEN];			/*����·��*/
	char license[FACE_LICENSE_LEN];		/*���֤��*/
}FACE_INFO_T, *PFACE_INFO_T;

typedef struct tagAlarm
{
	int detailType;
	int channel;
	char stime[NET_APP_DATE_LEN];
	char picName[PATH_MAX_LEN];
	char videoName[PATH_MAX_LEN];
}ALARM_INFO_T,*PALARM_INFO_T;

typedef struct tagPeriheralState
{
	int state;
	char deviceName[CONTENT_MAX_LEN];
}PERI_STATE_T, *PPERI_STATE_T;

typedef struct tagVehicleNotify
{
	int state;
}VEHICLE_NOTIFY_T, *PVEHICLE_NOTIFY_T;

typedef struct tagPhotoTaken
{
	int type;
	int channel;
	int filesize;
	int result;
	char path[PATH_MAX_LEN];
	char thmPath[PATH_MAX_LEN];
	char startTime[NET_APP_DATE_LEN];
}PHOTO_TAKEN_T, *PPHOTO_TAKEN_T;

typedef struct tagfaceContrast
{
	int result;
	unsigned int similarity;
}FACE_CONTRAST_T, *PFACE_CONTRAST_T;

typedef struct tagUpgradeReq
{
	char* url;
}UPGRADE_REQ_T, *PUPGRADE_REQ_T;

typedef struct tagGear
{
	unsigned int gear;
}GEAR_T, *PGEAR_T;

typedef struct tagNotification
{
	char type[32];
	union {
		ALARM_INFO_T alarm;
		PERI_STATE_T peripheral;
		VEHICLE_NOTIFY_T vehicle;
		PHOTO_TAKEN_T photoTaken;
		FACE_CONTRAST_T faceResult;
		UPGRADE_REQ_T upgrade;
		GEAR_T gear;
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

typedef struct tagCertify
{
	unsigned int operate;
	unsigned int id;
	unsigned int type;
	unsigned int startTime;
	unsigned int endTime;
	unsigned int len;
	char detail[CERTIFY_MAX_LEN];
}CERITFY_T, *PCERITFY_T;

typedef struct tagGpsPoint
{
	unsigned int latitude; 			/* γ��*/
	unsigned int longtitude;		/*����*/
}GPS_POINT, *PGPS_POINT;

typedef struct tagCircleArea
{
	unsigned int radius;
	GPS_POINT center;			/*���ĵ�*/
}CIRCLE_AREA_T, *PCIRCLE_AREA_T;

typedef struct tagRectArea
{
	GPS_POINT leftPoint;		/*���ϵ�*/
	GPS_POINT rightPoint;	/*���µ�*/
}RECT_AREA_T, *PRECT_AREA_T;

typedef struct tagPolygonArea
{
	GPS_POINT vertex[MAX_POLYGON_VERTEX_NUM];
	unsigned int num;
}POLYGON_AREA_T, *PPOLYGON_AREA_T;

typedef struct tagRouteArea
{
	GPS_POINT inflctPoint[MAX_INFLECTION_POINT_NUM];
	unsigned int width[MAX_INFLECTION_POINT_NUM];
	unsigned int num;
}ROUTE_AREA_T, *PROUTE_AREA_T;

typedef struct tagArea
{
#define radius circle.radius
#define center circle.center
#define leftPoint rect.leftPoint
#define rightPoint rect.rightPoint
#define vertex polygon.vertex
#define vertexNum polygon.num
#define inflctPoint line.inflctPoint
#define lineWidth line.width
#define pointNum line.num

	union {
		CIRCLE_AREA_T circle;
		RECT_AREA_T rect;
		POLYGON_AREA_T polygon;
		ROUTE_AREA_T line;
	};
	unsigned int id;			/*����ID*/
	unsigned int property;		/*��������*/
	unsigned int type;			/*��������*/
	
	char startTime[NET_APP_DATE_LEN];
	char endTime[NET_APP_DATE_LEN];
}AREA_T, *PAREA_T;

typedef struct tagAreaInfo
{
	int operate;		/*����*/
	unsigned int areaNum; /*��������*/
	AREA_T area[MAX_AREA_NUM];
}AREA_INFO_T, *PAREA_INFO_T;

typedef struct tagFileCriteria
{
	int type;	/*¼�����͡�0-��ͨ¼��1-����¼��2-�ֶ�¼��(ƽ̨�·�)��3-�澯¼��9-ȫ��¼��(����0,1,2,3)*/
	int channel;/*ͨ���ţ���0��ʼ*/
	char startTime[NET_APP_DATE_LEN];
	char stopTime[NET_APP_DATE_LEN];
}FILE_CRITERIA_T, *PFILE_CRITERIA_T;

typedef struct tagFileInfo
{
	int lockState;
	unsigned int duration;
	unsigned int size;
	unsigned char type;
	char name[CONTENT_MAX_LEN];
	char startTime[NET_APP_DATE_LEN];
	
}FILE_INFO_T, *PFILE_INFO_T;

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
	int (*get_face_info)(int index, PFACE_INFO_T pInfo);
	int (*set_face_info)(int index, PFACE_INFO_T pInfo);
	int (*faceContrast)(const char* pic);
	int (*take_photo)(int channel, int type);
	int (*checkSelf)(void);
	int (*get_ceritfy_Num)(void);
	int (*get_ceritfy)(unsigned int id, PCERITFY_T pCeritfy);
	int (*get_area_Num)(void);
	int (*get_area)(unsigned int id, PAREA_T pArea);
	int (*upgrade_result)(unsigned int result, unsigned int progress);
	void* (*file_list_get)(unsigned int type, PFILE_CRITERIA_T pCriteria, unsigned int* num);
	int (*search_file_next)(int reverse, void *h, PFILE_INFO_T pFileInfo);
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
 * @brief ��ȡ��׿������״̬
 * @return ���ߣ�true�����ߣ�false
 */
int net_termianl_is_inline();

/**
 * @brief ��ȡ������ָ��
 * @param mod ģ������
 * @param level �ȼ� 4:�رգ�3:���еȼ� 2:trace������ 1:warning������ 0:error
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_debug_set(const char* mod, int level);

/**
 * @brief ��ȡ�汾��Ϣ
 * @param buf ������ 
 * @param len ��Ϣ������
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_get_version(char* buf, unsigned int len);

/**
 * @brief �������Ƿ�Ϸ�
 * @param url ������·�� 
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_upgrade_check(const char* url);

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

/**
 * @brief �����ԱȽ������
 * @param result �ԱȽ��
 * @param similarity ���ƶ�
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
void net_terminal_face_contrast_result(int result, unsigned int similarity);

/**
 * @brief ����Բ�ε���Χ��
 * @param operate :����
 * @param p :����Χ����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_circle_area_set(int operate, void* p);

/**
 * @brief ���þ��ε���Χ��
 * @param operate :����
 * @param p :����Χ����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_rect_area_set(int operate, void* p);

/**
 * @brief ���ö���ε���Χ��
 * @param operate :����
 * @param p :����Χ����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����Efalse
 */
int net_terminal_polygon_area_set(int operate, void* p);

/**
 * @brief ����·��
 * @param operate :����
 * @param p :·����Ϣ
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_line_area_set(int operate, void* p);

/**
 * @brief ɾ������Χ��
 * @param type :����Χ������
 * @param total :ɾ������
 * @param pId :ɾ��ID�б�
 * @return �ɹ�������true��ʧ�ܣ�����false
 */
int net_terminal_area_delete(int type, unsigned int total, unsigned int * pId);


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
