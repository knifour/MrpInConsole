#include <schar.h>
#include <stdio.h>

SCHAR::SCHAR(){
  mValid = true;
	mFColor = ATTR::FWhite;
	mBColor = ATTR::BBlack;
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

void SCHAR::SetFColor(ATTR pFColor){
	mFColor = pFColor;
}

void SCHAR::SetBColor(ATTR pBColor){
	mBColor = pBColor;
}

ATTR SCHAR::GetFColor(void){
	return mFColor;
}

ATTR SCHAR::GetBColor(void){
	return mBColor;
}