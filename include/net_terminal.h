#ifndef __NET_TERMINAL_H__
#define __NET_TERMINAL_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define NET_APP_DEV_INFO_LEN 16
#define NET_APP_VERSION_LEN 32
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

/*�ⲿ�ӿں���*/
typedef struct tagAdapterFunc
{
	int (*device_info_get)(PDEV_INFO_T pstDevInfo);
}ADAPTER_T, *PADAPTER_T;

void net_termianl_init();

PADAPTER_T get_adapter();


#ifdef __cplusplus
}
#endif //__cplusplus
#endif //__NET_TERMINAL_H__
