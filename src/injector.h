#ifndef INJECTOR_H
#define INJECTOR_H
#include <windows.h>

class injector
{
public:
    injector(DWORD PID);
    DWORD pid;
};

#endif // INJECTOR_H
