#ifndef __THREAD_H__
#define __THREAD_H__
#include "TFuncation.h"

namespace Infra
{

struct MutexInternal;

class CMutex
{
public:
	CMutex();
	virtual ~CMutex();
	bool lock();
	bool trylock();
	bool unlock();
private:
	struct MutexInternal* m_pInternal;
};

template <class T>
class CGuard
{
public:
	inline CGuard(T & lock):m_lock(lock)
	{
		m_lock.lock();
	}
	inline ~CGuard()
	{
		m_lock.unlock();
	}
private:
	T & m_lock;
};

struct CondInternal;

class CCondSignal
{
public:
	CCondSignal();
	virtual ~CCondSignal();
	bool wait();
	bool signal();
private:
	struct CondInternal* m_pInternal;
};


struct ThreadInternal;
typedef TFuncation1<void, void *> ThreadProc_t;
/**
* @brief �̻߳���
**/
class IThread
{
friend struct ThreadInternal;
protected:
	IThread();
	virtual ~IThread();
	int create(struct ThreadInternal* pInternal);
	struct ThreadInternal* allocateThread();
	void releaseThread(struct ThreadInternal* pInternal);
	
	ThreadProc_t m_proc;
	struct ThreadInternal* m_pInternal;
};

/**
* @brief �߳���
**/
class CThread : public IThread
{
public:
	CThread();
	virtual ~CThread();
	/**
	* @brief �����̣߳��������̴߳��ڹ���״̬
	* @param isBlock �Ƿ��������ķ�ʽ�����̡߳�
	* @return true:�ɹ���false:ʧ��
	**/
	bool createTread(bool isBlock = false);

	/**
	* @brief �߳̿�ʼ����
	* @param isLoop �Ƿ�ֻ����һ�Ρ�
	**/
	void run(bool isLoop = true);

	/**
	* @brief �̹߳���
	* @param isBlock �Ƿ�ȴ��̹߳����ŷ���
	**/
	void suspend(bool isBlock = false);

	/**
	* @brief �����̼߳�������
	**/
	void pasue();

	/**
	* @brief �߳���ֹ����
	* @param isBlock �Ƿ�ȴ��߳��˳���ŷ���
	* @return true:�ɹ���false:ʧ��
	**/
	bool stop(bool isBlock = false);

	/**
	* @brief ע���߳�ִ�к���
	* @param proc ִ�к���
	* @return true:�ɹ���false:ʧ��
	**/
	bool attachProc(const ThreadProc_t & proc);

	/**
	* @brief ע���߳�ִ�к���
	* @param proc �Ѿ�ע�����ִ�к���
	* @return true:�ɹ���false:ʧ��
	**/
	bool detachProc(const ThreadProc_t & proc);

	/**
	* @brief �߳��Ƿ��Ѿ��ɹ�������createTread��
	* @return true:�Ѵ�����false:δ����
	**/
	bool isTreadCreated() const;
};

} //Infra

#endif //__THREAD_H__
