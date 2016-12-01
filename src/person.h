#ifndef PERSON_H
#define PERSON_H
#include "process.h"

class Person
{
public:
	Person(DWORD PID);
	wchar_t* getName();
	DWORD getHP();
	float getX();
	float getY();
	float getZ();
private:
	void reInit();
	Process *prc;
	wchar_t Name [20];
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
