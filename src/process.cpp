#include "process.h"
#include "addr.h"
#include <Windows.h>
#include <cstring>
#include <iostream>

HWND winH;
BOOL CALLBACK enumWindowsProc(HWND hwnd, LPARAM lParam)
{
	DWORD bpid;
	char ClName[50];
	GetWindowThreadProcessId(hwnd, &bpid);
	if (bpid == lParam) {
		GetClassName(hwnd, ClName, sizeof(ClName));
		if (!strcmp(ClName, "ElementClient Window")) {
			winH = hwnd;
			return false;
		}
	}
	else return true;
}
Process::Process(DWORD PID){
	pid = PID;
	prHandle = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
	EnumWindows(enumWindowsProc, pid);
	winHandle = winH;
	SetWindowPos(winHandle, HWND_TOP, -8, -31, 1382, 766, SWP_SHOWWINDOW);
}
Process::~Process() {
	CloseHandle(prHandle);
}
byte Process::readMem_b(DWORD addr) {
	byte value;
	ReadProcessMemory(prHandle, (void*)addr, &value, sizeof(value), 0);
	return value;
}
DWORD Process::readMem(DWORD addr){
    DWORD value;
    ReadProcessMemory(prHandle, (void*)addr, &value, sizeof(value), 0);
    return value;
}
float Process::readMem_f(DWORD addr){
    float value;
    ReadProcessMemory(prHandle, (void*)addr, &value, sizeof(value), 0);
    return value;
}
wchar_t* Process::readMem_20s(DWORD addr)
{
	wchar_t value[20];
	for (int i = 0; i < 20; i++) {
		ReadProcessMemory(prHandle, (void*)(addr + sizeof(value[i]) * i), &value[i], sizeof(value[i]), 0);
	}
	return value;
}
DWORD Process::jumpToPersStruct(){
	return readMem(readMem(GameAddr) + PersStruct);
}
DWORD Process::jumpToPersInventory() {
	return readMem(jumpToPersStruct() + PersInv);
}
DWORD Process::givepid(){
	return pid;
}