#include <iostream>
#include "son.h"

using namespace std;

SON::SON(){
	mSon = 10;
}

void SON::setSon(int value){
	mSon = value;
}

bool SON::operator==(const FATHER& rhs){
	if (mBase == rhs.getBase()){
		if (mSon == rhs.getSon())
  	  return true;
	}
	
	return false;
}

FATHER& SON::operator=(const FATHER& rhs){
	mBase = rhs.getBase();
	mSon  = rhs.getSon();
	
	return *this;
}

void SON::printMember(){
	cout << "Father: " << mBase << endl;
	cout << "Son: " << mSon << endl;
}

int SON::getSon() const {
	return mSon;
}