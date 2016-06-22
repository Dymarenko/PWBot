#include "person.h"
#include "addr.h"
#include <iostream>
Person::Person(){
	prc = new Process;
	//HP = prc->readMem(prc->jumpToPersStruct() + 0x494);
	HP = 0;
	
}
void Person::get(){
	std::cout<<"HP:"<<HP<<"\n";
}