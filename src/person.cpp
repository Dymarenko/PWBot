#include "person.h"
#include "addr.h"
#include <iostream>
Person::Person(){
	prc = new Process;
	HP = prc->readMem(prc->jumpToPersStruct() + PersHP);
	x = prc->readMem_f(prc->jumpToPersStruct() + PersXcoord);

}
void Person::get(){
	std::cout<<"X:"<<x<<"\n";
	std::cout<<"HP:"<<HP<<"\n";
}
