#include <iostream>
#include "father.h"

using namespace std;

FATHER::FATHER(){
	mBase = 35;
}

void FATHER::setValue(int value){
	mBase = value;
}

bool FATHER::operator==(const FATHER& rhs){
	if (mBase == rhs.mBase)
		return true;
	else
		return false;
}

void FATHER::printMember(){
	cout << "Father: " << mBase << endl;
}