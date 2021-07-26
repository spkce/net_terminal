#ifndef __PUSH_NOTIFICASION_H__
#define __PUSH_NOTIFICASION_H__

#include "Order.h"

namespace Screen
{

class CPushNotification : public IOrder
{
	//����������
public:
	virtual ~CPushNotification() {};

	/**
	* @brief ֪ͨ
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int notification(char* buf, int len, Json::Value &send);

	/**
	* @brief ������Ϣ֪ͨ
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int sendWarnInfo(char* buf, int len, Json::Value &send);

	/**
	* @brief �Լ���Ϣ֪ͨ
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int sendCheckInfo(char* buf, int len, Json::Value &send);

	/**
	* @brief ��Ϣ֪ͨ
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int sendClientMessage(char* buf, int len, Json::Value &send);

	/**
	* @brief ���֤֪ͨ
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int sendLicense(char* buf, int len, Json::Value &send);

	/**
	* @brief ����Χ��֪ͨ
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int sendArea(char* buf, int len, Json::Value &send);

	/**
	* @brief ��յ���Χ��
	* @param buf ��������
	* @param len ��������
	* @param send ���ͱ���
	* @return ������
	**/
	static int sendClearArea(char* buf, int len, Json::Value &send);
};

}//Screen
#endif
