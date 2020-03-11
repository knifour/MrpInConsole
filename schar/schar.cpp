#include <schar.h>
#include <stdio.h>

SCHAR::SCHAR(){
  mValid = true;
	mUnderLine = false;
	mFColor = 7;
	mBColor = 0;
}

bool SCHAR::operator==(const SCHAR &rhs){
	if (mFColor != rhs.mFColor)
		return false;
	if (mBColor != rhs.mBColor)
		return false;
	
	return true;
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