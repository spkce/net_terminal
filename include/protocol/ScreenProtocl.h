#ifndef __SCREEN_PROTOCL_H__
#define __SCREEN_PROTOCL_H__

namespace Screen
{

class IScreenProtocl
{
protected:
	IScreenProtocl();
	virtual ~IScreenProtocl();
public:
	static IScreenProtocl * getInstance();

	virtual bool parse(char* buf, int len) = 0;
};





} //Screen

#endif //__SCREEN_PROTOCL_H__
