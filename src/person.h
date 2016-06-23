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
	float y;
	float x;
	int MP;
	int HP;
};

#endif // PERSON_H
