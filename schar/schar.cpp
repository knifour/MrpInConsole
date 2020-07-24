#include <schar.h>
#include <stdio.h>

SCHAR::SCHAR(){
  mValid = true;
	mUnderLine = false;
	mFColor = 7;
	mBColor = 0;
}

void SCHAR::operator=(const SCHAR& rhs){
	mValid = rhs.mValid;
	mUnderLine = rhs.mUnderLine;
	mFColor = rhs.mFColor;
	mBColor = rhs.mBColor;
	
	for(int k=0; k<MAXBYTES; k++){
		mCode[k] = rhs.mCode[k];
	}
}

bool SCHAR::operator==(const SCHAR& rhs){
	bool result = true;
	
	for(int k=0; k<MAXBYTES; k++){
		if (mCode[k]==0 || rhs.mCode[k]==0)
			break;
		if (mCode[k] != rhs.mCode[k]){
			result = false;
			break;
		}
	}
	
	return result;
}

bool SCHAR::isValid(void){
	return mValid;
}

void SCHAR::setValid(const bool p){
	mValid = p;
}

void SCHAR::setUnderLine(bool p){
	mUnderLine = p;
}

void SCHAR::setFColor(int pFColor){
	mFColor = pFColor;
}

void SCHAR::setBColor(int pBColor){
	mBColor = pBColor;
}

int SCHAR::getFColor(void){
	return mFColor;
}

int SCHAR::getBColor(void){
	return mBColor;
}