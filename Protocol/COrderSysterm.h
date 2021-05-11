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
