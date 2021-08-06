#include <schar.h>
#include <stdio.h>

SCHAR::SCHAR(){
  mValid = true;
	mUnderLine = false;
	mFColor = 7;
	mBColor = 0;
}

// 判斷是否為有效字元
bool SCHAR::isValid(void) const{
	return mValid;
}

bool SCHAR::getUnderLine(void) const{
	return mUnderLine;
}

// 設定是否為有效字元
void SCHAR::setValid(const bool p){
	mValid = p;
}

// 設定是否劃底線
void SCHAR::setUnderLine(bool p){
	mUnderLine = p;
}

// 以顏色代碼設定前景色，顏色代碼超出範圍無效
void SCHAR::setFColor(int p){
	if (p>=0 && p<=255)
		mFColor = p;
}

// 以RGB值設定前景色，RGB值範圍為0~5
void SCHAR::setFColor(int r, int g, int b){
	setFColor(16 + r*36 + g*6 + b);
}

// 以顏色代碼設定背景色，顏色代碼超出範圍無效
void SCHAR::setBColor(int p){
	if (p>=0 && p<=255)
		mBColor = p;
}

// 以RGB值設定背景色，RGB值範圍為0~5
void SCHAR::setBColor(int r, int g, int b){
	setBColor(16 + r*36 + g*6 + b);
}

// 取得前景色
int SCHAR::getFColor(void) const{
	return mFColor;
}

// 取得背景色
int SCHAR::getBColor(void) const{
	return mBColor;
}