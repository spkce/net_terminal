#ifndef __TERMINAL_H__
#define __TERMINAL_H__

namespace Terminal
{

class ITerminal
{
public:
	enum
	{
		emTerminalScree,	
	};
protected:
	ITerminal();
	virtual ~ITerminal();
	
public:
	virtual bool init() = 0;

protected:
	int m_type;
};

} // Terminal
#endif //__TERMINAL_H__
