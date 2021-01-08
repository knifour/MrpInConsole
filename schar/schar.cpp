#include <schar.h>
#include <stdio.h>

SCHAR::SCHAR(){
  mValid = true;
	mUnderLine = false;
	mFColor = 7;
	mBColor = 0;
}

// 複製螢幕字元
/*void SCHAR::operator=(const SCHAR& rhs){
	mValid = rhs.mValid;
	mUnderLine = rhs.mUnderLine;
	mFColor = rhs.mFColor;
	mBColor = rhs.mBColor;
	
	// 確保在有效字元編碼之後都是0
	for(int k=0; k<MAXBYTES; k++) mCode[k]=0;
	
	for(int k=0; k<MAXBYTES; k++) mCode[k] = rhs.mCode[k];
}

// 判斷兩螢幕字元是否相等(字元編碼完全相同即視為相等)
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
}*/

// 判斷是否為有效字元
bool SCHAR::isValid(void){
	return mValid;
}

bool SCHAR::getUnderLine(void){
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
int SCHAR::getFColor(void){
	return mFColor;
}

// 取得背景色
int SCHAR::getBColor(void){
	return mBColor;
}