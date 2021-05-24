#ifndef __NET_TERMINAL_H__
#define __NET_TERMINAL_H__
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

#define NET_APP_DEV_INFO_LEN 16
#define NET_APP_VERSION_LEN 32
/**
 * @brief 获取设备信息
 */

typedef struct tagDevInfo
{
    unsigned int uDDR;
    unsigned int uLanguage;
    char  sDeviceType[NET_APP_DEV_INFO_LEN];/*设备型号，AE-CN2213-C1*/
    char  sFirmVersion[NET_APP_DEV_INFO_LEN];/*固件版本，V1.1.0*/
    char  sFirmDate[NET_APP_DEV_INFO_LEN];/*固件日期，2016.04.15*/
    char  sParamVersion[NET_APP_DEV_INFO_LEN];/*参数版本，V1.2.0*/
    char  sSerialNum[NET_APP_DEV_INFO_LEN];/*序列号，585022848*/
    char  sVerifyCode[NET_APP_DEV_INFO_LEN];/*设备验证码，HNDAGK*/
    char  sCustomID[NET_APP_DEV_INFO_LEN];/*定制单号*/
    char  sHardwareVer[NET_APP_DEV_INFO_LEN];/*硬件版本，V1.1.0*/
    char  sMCUVer[NET_APP_VERSION_LEN];/*MCU版本号*/
    char  sDspVer[NET_APP_VERSION_LEN];/*DSP版本号*/
    char  sFpgaVer[NET_APP_VERSION_LEN];/*FPGA版本号*/
	char  sGpsVer[NET_APP_VERSION_LEN];/*GPS版本号*/
}DEV_INFO_T, *PDEV_INFO_T;

/*外部接口函数*/
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
