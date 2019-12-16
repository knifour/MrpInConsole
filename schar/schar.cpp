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

bool SCHAR::IsValid(void){
	return mValid;
}

void SCHAR::SetValid(const bool p){
	mValid = p;
}

void SCHAR::SetUnderLine(bool p){
	mUnderLine = p;
}

void SCHAR::SetFColor(int pFColor){
	mFColor = pFColor;
}

void SCHAR::SetBColor(int pBColor){
	mBColor = pBColor;
}

int SCHAR::GetFColor(void){
	return mFColor;
}

int SCHAR::GetBColor(void){
	return mBColor;
}