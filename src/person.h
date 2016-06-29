#include "process.h"
#ifndef PERSON_H
#define PERSON_H

class Person
{
public:
	Person();
	void get();
private:
	void reInit();
	Process *prc;
	wchar_t *Name;
	float x;
	float y;
	float z;
	byte Med;
	DWORD invC;
	DWORD Lvl;
	DWORD MP;
	DWORD HP;
	DWORD EXP;
	DWORD targetWID;
};

#endif // PERSON_H
