#ifndef __NET_PROTOCL_H__
#define __NET_PROTOCL_H__
#include "IProtocl.h"
#include "jsoncpp.h"
#include "aes_encrypt.h"
#include "rsa_app.h"
#include "Session.h"

namespace NetServer {
	class ISession;
}

namespace Terminal {
	class ITerminal;
}

namespace Screen
{

/**
* @brief 汽车电子设备通信协议类
**/
class CNetProtocl: public IProtocl
{
#define NET_APP_EXTRA_LEN                       16          /*附加编码缓冲区大小*/
#define AES_MAX_IN_LEN                          16384        /*16KB*/
#define AES_MAX_OUT_LEN                         ((AES_MAX_IN_LEN) + (NET_APP_EXTRA_LEN))
#define AES_MAX_OUT_LEN_BASE64                  (AES_MAX_OUT_LEN*2)
#define MSG_HEADER_LENGTH                       12          /*消息头字节*/
#define NET_APP_RECV_SIZE                       2048        /*接收缓冲区大小*/
#define NET_APP_RECV_ADD                        ((NET_APP_RECV_SIZE) + (NET_APP_EXTRA_LEN))
	enum
	{
		aesKeyLength = 16,
	};
	/**
	* @brief 返回APP端参数
	*/
	typedef struct Param_t
	{
		unsigned int uTokenId;	/*令牌ID*/
		unsigned int uMsgId;	/*命令ID*/
		unsigned int uReqIdx;	/*消息索引*/
		unsigned int uEncrypt;	/*是否需要加密*/
	} Param_t;

#define MSG_HEADER_CONS                         0x41424243  /*消息头起始码ABBC*/
	/**
	 * @brief DEVICE->APP消息头部信息
	 */
	struct msgHeader
	{
		unsigned int uMsgConstant;    /*起始码ABBC*/
		unsigned int uMsgIndex;       /*消息编号，1...n，与消息类型ID不同*/
		unsigned int uMsgLength;      /*消息报文长度*/
	}msgHeader;
public:
	/**
	* @brief 构造函数，
	* @param terminal 终端指针
	**/
	CNetProtocl(Terminal::ITerminal* terminal);
	/**
	* @brief 析构函数，
	**/
	virtual ~CNetProtocl();
	/**
	* @brief 报文解析
	* @param session 会话话指针
	* @param buf 接收到的内容
	* @param len 接收到的内容长度
	* @return 成功/失败
	**/
	virtual bool parse(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief 封装消息发送,具体协议类必须实现
	* @param session 会话话指针
	* @param buf 接收到的内容
	* @param len 接收到的内容长度
	* @return 成功/失败
	**/
	virtual bool notify(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief 消息分发
	* @param session 会话话指针
	* @param msgID 消息ID
	* @param request 请求报文
	* @param response 回复
	* @return 成功/失败
	**/
	bool msgHub(NetServer::ISession * session, unsigned int msgID, Json::Value &request, Json::Value &response);
	/**
	* @brief 登录
	* @param session 会话话指针
	* @return 成功/失败
	**/
	bool login(NetServer::ISession* session, Json::Value &request, Json::Value &response);
	/**
	* @brief 登出
	* @param session 会话话指针
	* @return 成功/失败
	**/
	bool logout(NetServer::ISession* session);
	/**
	* @brief 保活
	* @param session 会话话指针
	* @return 成功/失败
	**/
	bool keepAlive(NetServer::ISession* session);
private:
	/**
	* @brief 消息处理
	* @param session 会话话指针
	* @param buf 接收到的内容
	* @param len 接收到的内容长度
	* @return 成功/失败
	**/
	bool messageProcess(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief 处理握手请求
	* @param session 会话话指针
	* @param request 请求报文
	* @param response 回复报文
	* @return 成功/失败
	**/
	bool handShake(NetServer::ISession* session, char* buf, int len);
	/**
	* @brief 检查报文协议头
	* @param buf 接收到的内容
	* @param index 消息index 每次通讯+1
	* @param len 接收到的内容长度
	* @return 成功/失败
	**/
	bool headerCheck(const char *buf, unsigned int *index, unsigned int * len);
	/**
	* @brief 解密
	* @param buf 待解码的内容
	* @param len 待解码的内容长度
	* @param decodeBuf 解码后的内容
	* @param Length 解码后的内容长度
	* @return 成功/失败
	**/
	bool decrypt(const char* buf, int len, char* decodeBuf, int* Length);
	/**
	* @brief 加密
	* @param buf 待加密的内容
	* @param len 待加密的内容长度
	* @param encryptBuf 加密后的内容
	* @param Length 加密后的内容长度
	* @return 成功/失败
	**/
	bool encrypt(const char* buf, int len, unsigned char* encryptBuf, int* Length);
	/**
	* @brief 发送回包
	* @param session 会话话指针
	* @param param 返回APP端参数
	* @param buf 发送的报文
	* @param len 发送的报文长度
	* @return 成功/失败
	**/
	bool reply(NetServer::ISession* session, Param_t* param, const char *buf, int len);
	/**
	* @brief 发送包
	* @param session 会话话指针
	* @param param 返回APP端参数
	* @param buf 发送的报文
	* @param len 发送的报文长度
	* @return 成功/失败
	**/
	bool sendPacket(NetServer::ISession* session, Param_t* param, const char *buf, int len);

	Terminal::ITerminal* m_pTerminal; //终端指针

	unsigned char m_AesKey[aesKeyLength]; //aes密钥

	int m_tokenId; //teokenId
	unsigned int m_reqIndex; //请求index
	
};


}//Screen

#endif // __NET_PROTOCL_H__
