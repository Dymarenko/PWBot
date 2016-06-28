#ifndef INJECTOR_H
#define INJECTOR_H
#include <windows.h>

class injector
{
public:
    injector();
    void targetmob(DWORD wid);
	void setFuncAlloc();
    DWORD pid;
private:
    void* pFunc;
    void* pParams;
    byte injectAndExecute(void* func, void* param);
};

#endif // INJECTOR_H
