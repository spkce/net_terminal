
#include "stdio.h"
#include "ctime.h"
#include <sys/select.h>
#include <errno.h>

namespace Infra
{

unsigned long long CTime::getRealTimeSecond()
{
	timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return time.tv_sec;
}


unsigned long long CTime::getRealTimeMSecond()
{
	timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	return time.tv_nsec /1000000 + time.tv_sec* 1000;
}

unsigned long long CTime::getSystemTimeSecond()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	return time.tv_sec;
}

unsigned long long CTime::getSystemTimeMSecond()
{
	timespec time;
	clock_gettime(CLOCK_MONOTONIC, &time);
	return time.tv_nsec /1000000 + time.tv_sec* 1000;
}

unsigned long long CTime::getProcessTimeSecond()
{
	timespec time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time); 
	return time.tv_sec;
}

unsigned long long CTime::getProcessTimeMSecond()
{
	timespec time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &time);
	return time.tv_nsec /1000000 + time.tv_sec* 1000;
}

unsigned long long CTime::getThreadTimeSecond()
{
	timespec time;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time);
	return time.tv_sec;
}

unsigned long long CTime::getThreadTimeMSecond()
{
	timespec time;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &time);
	return time.tv_nsec /1000000 + time.tv_sec* 1000;
}

void CTime::covertRealTime(unsigned int ms, timespec *tp)
{
	unsigned long long _ms = getRealTimeMSecond() + ms;

	tp->tv_sec = _ms/1000;
	tp->tv_nsec = (_ms%1000)*1000;
}

void CTime::delay_ms(unsigned int ms)
{
	struct timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = ms;
	int err;
	do
	{
		err = select(0,NULL,NULL,NULL,&tv);
	}while (err<0 && errno==EINTR);
}

}//Infra
