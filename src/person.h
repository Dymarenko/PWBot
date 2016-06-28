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
	DWORD MP;
	DWORD HP;
	DWORD EXP;
};

#endif // PERSON_H
