#ifndef __SESSION_H__
#define __SESSION_H__

#include "thread.h"
#include "timer.h"
#include <vector>

namespace NetServer
{

/**
* @brief �Ự����
**/
class ISession
{
public:
	/**
	* @brief session �ص���������
	**/
	typedef Infra::TFuncation3<void, ISession*, char*, int> SessionProc_t;
	
	/**
	* @brief session ״̬
	**/
	typedef  enum state_t
	{
		emStateCreated,
		emStateLogout,
		emStateLogin,
		emStateClose,
		emStateNone,
	}state_t;
protected:
	/**
	* @brief ���캯���� �趨protectedȨ�ޣ�����ʵ�����ɼ̳�
	**/
	ISession(){};
	
	/**
	* @brief ���������� �趨protectedȨ�ޣ�����ʵ�����ɼ̳�
	**/
	virtual ~ISession(){};

public:
	/**
	* @brief �󶨻ص�����
	* @param proc �ص�����
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool bind(const SessionProc_t & proc) = 0;

	/**
	* @brief ����ص�����
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool unbind() = 0;

	/**
	* @brief ��¼
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool login() = 0;

	/**
	* @brief �ǳ�
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool logout() = 0;
	
	/**
	* @brief ����
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool keepAlive() = 0;
	
	/**
	* @brief �Ƿ�ʱ
	* @return ��ʱ��true��δ��ʱ��false
	**/
	virtual bool isTimeout() = 0;

	/**
	* @brief ��ȡ�Ự״̬
	* @return ��ȡ�Ự״̬
	**/
	virtual state_t getState() = 0;

	/**
	* @brief �رջỰ
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool close() = 0;

	/**
	* @brief �Ự�ͷ�
	**/
	virtual void destroy() = 0;

	/**
	* @brief ������Ϣ��ͬ��
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	* @return ���͵����ݳ���
	**/
	virtual int send(const char* buf, int len) = 0;

	/**
	* @brief ������Ϣ���첽
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	* @return ��ȡ�Ự״̬
	**/
	virtual bool transmit(const char* buf, int len) = 0;
};

/**
* @brief �Ự������
**/
class CSessionManager
{
private:
	/**
	* @brief ���캯���� �趨privateȨ�ޣ��ⲿ����ʵ�������ɼ̳�
	**/
	CSessionManager();
	/**
	* @brief ���������� �趨privateȨ�ޣ��ⲿ����ʵ�������ɼ̳�
	**/
	~CSessionManager();

public:
	/**
	* @brief ��ȡ�Ự������ʵ��
	**/
	static CSessionManager* instance();

	/**
	* @brief ����session
	* @param sockfd �׽��־��
	* @param addr �Զ˵�ַ
	* @param timeout ��ʱʱ�䵥λ�룬Ĭ��ֵ-1 ���ᳬʱ
	* @return �Ự����ָ��
	**/
	ISession* createSession(int sockfd, struct sockaddr_in* addr, int timeout = -1);
	/**
	* @brief ȡ��session
	* @param session �Ự����ָ��
	**/
	bool cancelSession(ISession* session);
	/**
	* @brief ��ѯsession�Ƿ�ע����
	* @param session ָ��
	* @return �Ƿ�ע��
	**/
	bool isSessionRegister(ISession* session);
	/**
	* @brief ��ѯsession״̬
	* @param session ָ��
	* @return ״̬
	**/
	int getState(ISession* session);
private:
	/**
	* @brief ע��session
	* @param session �Ự����ָ��
	**/
	void registerSession(ISession* session);
	/**
	* @brief ��ʱ���ص�����
	* @param arg ʱ�䣬ϵͳ����ʱ�����
	**/
	void timerProc(unsigned long long arg);

	Infra::CTimer m_timer;
	Infra::CMutex m_mutex;
	std::vector<ISession*> m_vecSession;
	
};



} //NetServer
#endif //__SESSION_H__