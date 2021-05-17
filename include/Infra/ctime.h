#ifndef __TIME_H__
#define __TIME_H__

namespace Infra
{

class CTime
{
public:
	//获取当前unix时间戳, 单位:秒
	static long getRealTimeSecond();
	//获取当前unix时间戳, 单位:毫秒
	static long getRealTimeMSecond();
	//获取系统运行时间, 单位:秒
	static long getSystemTimeSecond();
	//获取系统运行时间, 单位:纳秒
	static long getSystemTimeMSecond();
	//获取进程运行时间, 单位:秒
	static long getProcessTimeSecond();
	//获取进程运行时间, 单位:纳秒
	static long getProcessTimeMSecond();
	//获取线程运行时间, 单位:秒
	static long getThreadTimeSecond();
	//获取线程运行时间, 单位:纳秒
	static long getThreadTimeMSecond();

	static void delay_ms(unsigned int ms);
};

}//Infra

#endif //__TIME_H__
