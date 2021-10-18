#include <iostream>
#include "father.h"

using namespace std;

FATHER::FATHER(){
	mBase = 65;
}

FATHER::FATHER(int p){
	mBase = p;
}

void FATHER::setBase(int value){
	mBase = value;
}

/*bool FATHER::operator==(const FATHER& rhs){
	if (mBase == rhs.mBase)
		return true;
	else
		return false;
}

void FATHER::printMember(){
	cout << "Father: " << mBase << endl;
}*/

int FATHER::getBase() const{
	return mBase;
}