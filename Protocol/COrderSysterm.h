#ifndef __CORDER_SYSTERM_H__
#define __CORDER_SYSTERM_H__

#include "IOrder.h"

namespace Screen
{
class COrderSysterm : public IOrder
{
public:
	enum ErrCode
	{
		/*系统类错误码*/
		AE_SYS_NOERROR                          = 0,         /*正常*/
		AE_SYS_UNKNOWN_ERROR                    = 1,         /*操作异常，无法判定原因*/
		AE_SYS_SESSION_START_FAIL               = 2,         /*建立连接失败*/
		AE_SYS_INVALID_TOKEN                    = 3,         /*token错误*/
		AE_SYS_REACH_MAX_CLINT                  = 4,         /*客户端连接数达到上限*/
		AE_SYS_HDMI_INSERTED                    = 5,         /*APP请求建立连接时，HDMI端口有连接其他外设*/
		AE_SYS_NO_MORE_MEMORY                   = 6,         /*设备内存耗尽*/
		AE_SYS_PIV_NOT_ALLOWED                  = 7,         /*当前分辨率和帧率不支持在录像的时候抓拍图片*/
		AE_SYS_SYSTEM_BUSY                      = 8,         /*系统繁忙，无法处理当前请求*/
		AE_SYS_NOT_READY                        = 9,         /*设备初始化未完成*/
		AE_SYS_RESET_FAILED                     = 10,        /*设备复位失败*/
		AE_SYS_GET_FILE_LIST_FAILED             = 11,        /*获取文件列表失败*/
		AE_SYS_UNACTIVED                        = 12,        /*设备未激活*/
		AE_SYS_DEMO_MODE                        = 13,        /*设备处在演示模式，无法设置参数*/
		AE_NO_BATTERY                           = 14,        /*设备未装载电池*/
		AE_NO_TRAIN_INFO                        = 15,        /*未连接外部设备*/
	};
public:
	COrderSysterm();
	~COrderSysterm();

	int getCameraStatus(Json::Value &request, Json::Value &response);
};



} //Screen
#endif //__CORDER_SYSTERM_H__
