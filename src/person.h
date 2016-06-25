#include "process.h"
#ifndef PERSON_H
#define PERSON_H

class Person
{
public:
	Person();
	void get();
private:
	Process *prc;
	float x;
	float y;
	float z;
	DWORD MP;
	DWORD HP;
	DWORD EXP;
};

#endif // PERSON_H
