#include "strsafe.h"
class WinDebugInfo
{
public:
	WinDebugInfo()
	{
		AllocConsole();

		SetConsoleTitle("Debug Window");

		hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

		COORD coord = {80,25};

		SetConsoleScreenBufferSize(hStdOut, coord);
	}

	int PrintfInfo(char *fmt,...)
	{
		char sText[1024];

		va_list argptr;

		int nByte;

		va_start(argptr, fmt);

		nByte = vsprintf(sText, fmt, argptr);

		va_end(argptr);

		DWORD cCharsWritten;

		if(hStdOut)
			WriteConsole(hStdOut, sText, strlen(sText), &cCharsWritten, NULL);

		return nByte;
	}

private:
	HANDLE hStdOut;
};


