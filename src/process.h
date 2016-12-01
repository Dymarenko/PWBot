#include <windows.h>
#include <tlhelp32.h>

#ifndef PROCESS_H
#define PROCESS_H
class Process
{
public:
	Process(DWORD PID);
	~Process();

	DWORD Process::givepid();

	DWORD readMem(DWORD addr);
	float readMem_f(DWORD addr);
	byte readMem_b(DWORD addr);
	wchar_t* readMem_20s(DWORD addr);
	DWORD jumpToPersStruct();
	DWORD jumpToPersInventory();

private:
	DWORD pid;
	HANDLE prHandle;
	HWND winHandle;
	HWND scdwinHandle;
};
#endif
