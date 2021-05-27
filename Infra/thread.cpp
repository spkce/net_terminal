#include <unistd.h>
#include <pthread.h>
#include "thread.h"
#include "stdio.h"
#include <string.h>
#include <errno.h>
#include "TFuncation.h"
#include "link.h"
#include "logInternal.h"

namespace Infra
{

struct MutexInternal
{
	pthread_mutex_t mutex;
};

CMutex::CMutex()
{
	m_pInternal = new MutexInternal();
	pthread_mutex_init(&m_pInternal->mutex, NULL);
}

CMutex::~CMutex()
{
	pthread_mutex_destroy(&m_pInternal->mutex);
	delete m_pInternal;
	m_pInternal = NULL;
}

/**
* @brief ����������
* @return true:�ɹ���false:ʧ��
**/
bool CMutex::lock()
{
	return pthread_mutex_lock(&m_pInternal->mutex) == 0 ? true : false;
}

/**
* @brief ���Լ�����������
* @return true:�ɹ���false:ʧ��
**/
bool CMutex::trylock()
{
	return pthread_mutex_trylock(&m_pInternal->mutex) == 0 ? true : false;
}

/**
* @brief ����
* @return true:�ɹ���false:ʧ��
**/
bool CMutex::unlock()
{
	return pthread_mutex_unlock(&m_pInternal->mutex) == 0 ? true : false;
}

struct CondInternal
{
	pthread_cond_t cond;
	pthread_mutex_t mutex;
};

CCondSignal::CCondSignal()
{
	m_pInternal = new CondInternal();
	pthread_mutex_init(&m_pInternal->mutex, NULL);
	pthread_cond_init(&m_pInternal->cond, NULL);
}

CCondSignal::~CCondSignal()
{
	pthread_cond_destroy(&m_pInternal->cond);
	pthread_mutex_destroy(&m_pInternal->mutex);
	delete m_pInternal;
	m_pInternal = NULL;
}

/**
* @brief ����
* @return true:�ɹ���false:ʧ��
**/
bool CCondSignal::wait()
{
	pthread_mutex_lock(&m_pInternal->mutex);
	int ret = pthread_cond_wait(&m_pInternal->cond, &m_pInternal->mutex);
	pthread_mutex_unlock(&m_pInternal->mutex);

	return ret == 0 ? true : false;
}

/**
* @brief �������
* @return true:�ɹ���false:ʧ��
**/
bool CCondSignal::signal()
{
	return pthread_cond_signal(&m_pInternal->cond) == 0 ? true : false;
}

struct RwlockInternal
{
	pthread_rwlock_t rwlock;
};

CRwlock::CRwlock()
{
	m_pInternal = new RwlockInternal();
	pthread_rwlock_init(&m_pInternal->rwlock, NULL);

}

CRwlock::~CRwlock()
{
	pthread_rwlock_destroy(&m_pInternal->rwlock);
	delete m_pInternal;
	m_pInternal = NULL;
}

/**
* @brief �Ӷ���������
* @return true:�ɹ���false:ʧ��
**/
bool CRwlock::rLock()
{
	return pthread_rwlock_rdlock(&m_pInternal->rwlock) == 0 ? true : false;
}

/**
* @brief ��д��������
* @return true:�ɹ���false:ʧ��
**/
bool CRwlock::wLock()
{
	return pthread_rwlock_wrlock(&m_pInternal->rwlock) == 0 ? true : false;
}

/**
* @brief ���ԼӶ�����������
* @return true:�ɹ���false:ʧ��
**/
bool CRwlock::tryRLock()
{
	return pthread_rwlock_tryrdlock(&m_pInternal->rwlock) == 0 ? true : false;
}

/**
* @brief ���Լ�д����������
* @return true:�ɹ���false:ʧ��
**/
bool CRwlock::tryWLock()
{
	return pthread_rwlock_trywrlock(&m_pInternal->rwlock) == 0 ? true : false;
}

/**
* @brief ����
* @return true:�ɹ���false:ʧ��
**/
bool CRwlock::unLock()
{
	return pthread_rwlock_unlock(&m_pInternal->rwlock) == 0 ? true : false;
}

enum 
{
	THREAD_INIT,
	THREAD_READY,
	THREAD_SUSPEND,
	THREAD_EXCUTE,
	THREAD_WORK,
	THREAD_EXIT,
};

struct ThreadInternal
{
	pthread_t handle;
	Infra::CMutex mutex;
	Infra::CCondSignal cond;//�����̵߳Ĺ���
	bool bLoop;				//�߳�ִ�����Ƿ�ѭ��,���û�����
	bool bExit;				//�߳�ִ�����˳�,���û�����
	bool bSuspend;			//�߳���ͣ����,���û�����true,ִ��������false
	bool isDestoryBlock;	//��ʾ�߳��˳�ʱ�Ƿ���������ʽ�˳�
	int state;				//�߳�״̬,��proc����
	IThread* owner;
	
	static void* proc(void* arg);
};

void* ThreadInternal::proc(void* arg)
{
	bool isLoop = false;
	bool isExit = false;
	bool isSuspend = false;
	ThreadInternal* pInternal = (ThreadInternal*)arg;

	InfraTrace("thread proc run\n");
	pInternal->cond.signal();
	pInternal->state = THREAD_EXCUTE;
	InfraTrace("thread proc signal\n");
	do
	{
		pInternal->mutex.lock();
		isExit = pInternal->bExit;
		isSuspend = pInternal->bSuspend;
		pInternal->mutex.unlock();
		
		if (isExit)
		{
			break;
		}

		if (isSuspend)
		{
			pInternal->state = THREAD_SUSPEND;
			InfraTrace("thread proc wait\n");
			pInternal->cond.signal();
			pInternal->cond.wait();
			pInternal->state = THREAD_EXCUTE;
			continue;
		}
		
		pInternal->state = THREAD_WORK;

		if (pInternal->owner != NULL || !pInternal->owner->m_proc.isEmpty())
		{
			pInternal->owner->m_proc(arg);
		}
		else
		{
			//û��ִ�к���û��ע�������
			pInternal->bSuspend = true;
			continue;
		}
		
		pInternal->state = THREAD_EXCUTE;

		pInternal->mutex.lock();
		isLoop = pInternal->bLoop;
		pInternal->mutex.unlock();
	} while (isLoop);
	
	pInternal->state = THREAD_EXIT;

	return NULL;
}

IThread::IThread()
{

}

IThread::~IThread()
{

}

int IThread::create(struct ThreadInternal* pInternal)
{
	//TODO:�����̲߳���
	int err = pthread_create(&pInternal->handle, NULL, (void*(*)(void*))&ThreadInternal::proc, (void*)pInternal);
	if (err)
	{
		//�̴߳���ʧ��
		InfraTrace("create pthread error: %d\n",err);
		return err;
	}

	//�����߳�Ϊ�ɷ���״̬���߳����н�������Զ��ͷ���Դ��
	if (pthread_detach(pInternal->handle))
	{
		InfraTrace("detach pthread error: %d\n",err);
	}
	return err;
}

struct ThreadInternal* IThread::allocateThread()
{
	return  new ThreadInternal();
}

void IThread::releaseThread(struct ThreadInternal* pInternal)
{
	delete pInternal;
}

CThread::CThread()
{
	m_pInternal = allocateThread();
	m_pInternal->bLoop = false;
	m_pInternal->bExit = false;
	m_pInternal->bSuspend = true;
	m_pInternal->state = THREAD_INIT;
	m_pInternal->owner = this;
	m_pInternal->isDestoryBlock = true;

}

CThread::~CThread()
{
	stop();
	
	releaseThread(m_pInternal);
	m_pInternal = NULL;
}

void CThread::run(bool isLoop)
{
	InfraTrace("isLoop: %d\n", isLoop);
	if (m_pInternal->state == THREAD_EXIT)
	{
		return ;
	}
	m_pInternal->mutex.lock();
	m_pInternal->bLoop = isLoop;
	m_pInternal->bSuspend = false;
	m_pInternal->mutex.unlock();

	if (m_pInternal->state == THREAD_SUSPEND)
	{
		m_pInternal->cond.signal();
	}
}

void CThread::suspend(bool isBlock)
{
	if (m_pInternal->state == THREAD_EXCUTE || m_pInternal->state == THREAD_WORK)
	{
		m_pInternal->mutex.lock();
		m_pInternal->bSuspend = true;
		m_pInternal->mutex.unlock();
	}

	if (isBlock)
	{
		m_pInternal->cond.wait();	
	}	
}

void CThread::pasue()
{
	if (m_pInternal->state == THREAD_SUSPEND)
	{
		m_pInternal->mutex.lock();
		m_pInternal->bSuspend = false;
		m_pInternal->mutex.unlock();
		
		m_pInternal->cond.signal();
	}
}

bool CThread::stop(bool isBlock)
{
	if (m_pInternal->state == THREAD_INIT || m_pInternal->state == THREAD_EXIT)
	{
		return false;
	}

	m_pInternal->mutex.lock();
	m_pInternal->bExit = true;
	m_pInternal->bLoop = false;
	m_pInternal->mutex.unlock();

	pthread_t curTID = pthread_self(); 
	if (pthread_equal(curTID, m_pInternal->handle))
	{
		//�˺������߳�ִ������ã����ȴ�ֱ���˳�
		return true;
	}

	if (m_pInternal->state == THREAD_SUSPEND || m_pInternal->state == THREAD_READY)
	{
		m_pInternal->cond.signal();
	}

	if (isBlock)
	{
		//ʹ�������������ȴ��߳��˳�
		pthread_join(m_pInternal->handle, NULL);
	}

	return true;
}

bool CThread::attachProc(const ThreadProc_t & proc)
{
	if (m_pInternal->state == THREAD_EXCUTE 
		|| m_pInternal->state == THREAD_WORK
		|| m_pInternal->state == THREAD_EXIT)
	{
		return false;
	}

	if (m_proc.isEmpty())
	{
		m_proc = proc;
		return true;
	}

	return false;
}
	
bool CThread::detachProc(const ThreadProc_t & proc)
{
	if (m_pInternal->state == THREAD_EXCUTE 
		|| m_pInternal->state == THREAD_WORK
		|| m_pInternal->state == THREAD_EXIT)
	{
		return false;
	}

	if (!m_proc.isEmpty() && m_proc == proc)
	{
		m_proc.unbind();
		return true;
	}
	
	return false;
}

bool CThread::isTreadCreated() const
{
	return m_pInternal->state >= THREAD_READY;
}


bool CThread::createTread(bool isBlock)
{
	InfraTrace("isBlock: %d\n", isBlock);
	if (isTreadCreated())
	{
		//�߳��Ѿ�����
		return false;
	}
	
	if (create(m_pInternal))
	{
		//�̴߳���ʧ��
		m_pInternal->state = THREAD_EXIT;
		InfraTrace("create pthread error\n");
		return false;
	}

	m_pInternal->state = THREAD_READY;
	if (isBlock)
	{
		InfraTrace("create pthread error\n");
		m_pInternal->cond.wait();
	}

	return true;
}

}//Infra
