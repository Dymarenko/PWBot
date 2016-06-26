#include <windows.h>
#include <tlhelp32.h>
#ifndef PROCESS_H
#define PROCESS_H
class Process
{
public:
	DWORD givepid();
	Process();
	DWORD readMem(DWORD addr);
    float readMem_f(DWORD addr);
    wchar_t* readMem_9s(DWORD addr);
	DWORD jumpToPersStruct();
private:
	DWORD pid;
	void getPid(char* Name);
};
#endif
