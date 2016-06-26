#include "person.h"
#include "addr.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
Person::Person(){
	prc = new Process;
	HP = prc->readMem(prc->jumpToPersStruct() + PersHP);
	x = prc->readMem_f(prc->jumpToPersStruct() + PersXcoord);
    Name = prc->readMem_9s(prc->readMem(prc->jumpToPersStruct() + PersName) + 0x0);
}
void Person::get(){
	std::cout<<"X:"<<x<<"\n";
	std::cout<<"HP:"<<HP<<"\n";
	std::cout<<"Name:"<<Name<<"\n";
}
