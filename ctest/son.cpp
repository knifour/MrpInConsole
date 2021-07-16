#include <iostream>
#include "son.h"

using namespace std;

SON::SON(){
	mSon = 10;
}

void SON::setValue(int value){
	mSon = value;
}

bool SON::operator==(const SON& rhs){
	if (mBase == rhs.mBase){
		if (mSon == rhs.mSon)
			return true;
	}
	
	return false;
}

void SON::printMember(){
	cout << "Son: " << mSon << endl;
}