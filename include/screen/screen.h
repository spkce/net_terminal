#ifndef __SCREEN_H__
#define __SCREEN_H__
#include <vector>
#include "thread.h"
#include "terminal.h"
#include "MsgQueue.h"
#ifdef CONFIG_FENCE
#include "FenceManager.h"
#endif

struct sockaddr_in;

namespace NetServer {
	class INetServer;
	class ISession;
}
namespace Screen
{

class IProtocl;
class CScreen : public Terminal::ITerminal
{
public:
	/**
	* @brief ���캯��
	**/
	CScreen();

	/**
	* @brief ��������
	**/
	virtual ~CScreen();

	/**
	* @brief ��ʼ��
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool init();

	/**
	* @brief ��ȡ״̬
	* @return ״̬
	**/
	virtual int getState();

	/**
	* @brief session ����
	* @param session �Ựָ��
	* @param type Э������
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool connect(NetServer::ISession* session, int type);

	/**
	* @brief session �Ͽ�����
	* @param session �Ựָ��
	* @param type Э������
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool disconnet(NetServer::ISession* session, int type);
	/**
	* @brief ��ȡ�汾��Ϣ
	* @param ver �汾��Ϣ
	* @return �ɹ�/ʧ��
	**/
	virtual bool getVersion(std::string & ver);
	/**
	* @brief ��Ϣ����
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool notify(char* buf, int len);

	/**
	* @brief GPS��������
	* @param buf GPS��������
	* @param len GPS���ݳ���
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	virtual bool pushGps(char* buf, int len);
	
	/**
	* @brief �������ص�����
	* @param sockfd �׽��־��
	* @param addr �Զ��׽��ֵ�ַ
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	bool serverTask(int sockfd, struct sockaddr_in* addr);
	
	/**
	* @brief �Ự�ص�����
	* @param session �Ựָ��
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	**/
	void sessionTask(NetServer::ISession* session, char* buf, int len);
	
	/**
	* @brief GPS�����ص�����
	* @param sockfd �׽��־��
	* @param addr �Զ��׽��ֵ�ַ
	* @return �ɹ���true��ʧ�ܣ�false
	**/
	bool servGpsTask(int sockfd, struct sockaddr_in* addr);
	
	/**
	* @brief �Ự�ص�����
	* @param session �Ựָ��
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	**/
	void pushGpsTask(NetServer::ISession* session, char* buf, int len);

#ifdef CONFIG_FENCE
	/**
	* @brief Χ����Ϣ�ص�����
	* @param session �Ựָ��
	* @param buf ��Ϣ����
	* @param len ��Ϣ����
	**/
	void fenceTask(int event, int param1, int param2, void* p);
#endif

private:
#define PORT_MAIN 7877
#define PORT_GPS 8881
#define MAX_SESSION_MAIN 5
#define MAX_SESSION_GPS 1
	const int m_maxSession;
	const int m_maxGpsSession;
	const int m_portMain;
	const int m_portGps;
	NetServer::INetServer* m_pServMain;
	NetServer::INetServer* m_pServGps;
	IProtocl* m_protocl;
	IProtocl* m_protoclGps;
	NetServer::ISession* m_gpsSession;
	NetServer::ISession* m_mainSession;

};



} // Screen
#endif //__SCREEN_H__