#include "terminal.h"
#include "screen.h"
#include "NetServer.h"

namespace Terminal
{

ITerminal::ITerminal()
{
}

ITerminal::~ITerminal()
{
}

ITerminal* ITerminal::createTerminal(Terminal_t type)
{
	if (type == emTerminalScree)
	{
		return new Screen::CScreen();
	}
	else
	{
		return NULL;
	}
}

} // Terminal
