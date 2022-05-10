#include <iostream>
#include "grandson.h"

using namespace std;

GRANDSON::GRANDSON(){
	mGrandSon = 10;
}

void GRANDSON::setGrandSon(int value){
	mGrandSon = value;
}

bool GRANDSON::operator==(const FATHER& rhs){
	if (mBase == rhs.getBase()){
		if (mSon == rhs.getSon())
			if (mGrandSon == rhs.getGrandSon())
  	    return true;
	}
	
	return false;
}

FATHER& GRANDSON::operator=(const FATHER& rhs){
	mBase = rhs.getBase();
	mSon  = rhs.getSon();
	mGrandSon = rhs.getGrandSon();
	
	return *this;
}

void GRANDSON::printMember(){
	cout << "Father: " << mBase << endl;
	cout << "Son: " << mSon << endl;
	cout << "GrandSon: " << mGrandSon << endl;
}

int GRANDSON::getGrandSon() const {
	return mGrandSon;
}