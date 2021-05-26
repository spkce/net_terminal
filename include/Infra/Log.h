#ifndef __LOG_H__
#define __LOG_H__
#include <string>


enum emFontColor
{
	Font_black = 30,
	Font_red,
	Font_green,
	Font_yellow,
	Font_blue,
	Font_violet,
	Font_darkGreen,
	Font_white
};

enum emBackgroundColor
{
	background_black = 40,
	background_red,
	background_green,
	background_yellow,
	background_blue,
	background_violet,
	background_darkGreen,
	background_white
};

void exprintf(int fc, int bc, const char* fmt, ...) __attribute__((format(printf, 3, 4)));
void exprintf(int fc, const char* fmt, ...) __attribute__((format(printf, 2, 3)));

class CLog
{
public:
	enum emLogLevel
	{
		logLevel_0, //关闭所有打印
		logLevel_1,
		logLevel_2,
		logLevel_3,
		logLevel_4,
		logLevel_5
	};
	enum emLogType
	{
		type_onlyLog = 0,
		type_fileMsg,
		type_modMsg
	};
public:
	CLog(int logType, std::string name, std::string ver);
	~CLog();
	int setLogLevel(int lv);
	int getLogLevel();
	int getLogType();
	std::string getName();
	std::string getVer();

	//lv5
	void _info(const char* file, int line, const char* func, const char* fmt, ...) __attribute__((format(printf, 5, 6)));
	//lv4
	void _debug(const char* file, int line, const char* func, const char* fmt, ...) __attribute__((format(printf, 5, 6)));
	//lv3
	void _trace(const char* file, int line, const char* func, const char* fmt, ...) __attribute__((format(printf, 5, 6)));
	//lv2
	void _warning(const char* file, int line, const char* func, const char* fmt, ...) __attribute__((format(printf, 5, 6)));
	//lv1
	void _error(const char* file, int line, const char* func, const char* fmt, ...) __attribute__((format(printf, 5, 6)));
	
	#define info(fmt, ...) _info(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
	#define debug(fmt, ...) _debug(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
	#define trace(fmt, ...) _trace(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
	#define warning(fmt, ...) _warning(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
	#define error(fmt, ...) _error(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
private:
	int m_logType;
	int m_printLogLevel;
	std::string m_name;
	std::string m_ver;
};


class CGlobalLog
{
public:
	static CLog* instance();
private:
	CGlobalLog();
	~CGlobalLog();
public:
};

#define Info(fmt, ...) CGlobalLog::instance()->_info(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
#define Debug(fmt, ...) CGlobalLog::instance()->_debug(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
#define Trace(fmt, ...) CGlobalLog::instance()->_trace(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
#define Warning(fmt, ...) CGlobalLog::instance()->_warning(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)
#define Error(fmt, ...) CGlobalLog::instance()->_error(__FILE__, __LINE__, __FUNCTION__, (fmt), ## __VA_ARGS__)

#endif //__LOG_H__
