#include <utf8schar.h>
#include <stdio.h>

UTF8SCHAR::UTF8SCHAR(){
	for (int k=0; k<UTF8MAXLEN; k++) mCode[k] = 0;
	mCode[0] = 32;
}

UTF8SCHAR::UTF8SCHAR(int pFColor, int pBColor){
	mFColor = pFColor;
	mBColor = pBColor;
	for (int k=0; k<UTF8MAXLEN; k++) mCode[k] = 0;
	mCode[0] = 32;
}

UTF8SCHAR::UTF8SCHAR(const UTF8SCHAR& p){
	mValid = p.mValid;
	mUnderLine = p.mUnderLine;
	mFColor = p.mFColor;
	mBColor = p.mBColor;
	for (int i=0; i<UTF8MAXLEN; i++) mCode[i] = p.mCode[i];
}

UTF8SCHAR::UTF8SCHAR(const char* p){
	int len;
	
	for (int i=0; i<UTF8MAXLEN; i++)
		mCode[i] = 0;
	
	len = getFirstCharBytesU8((uint8_t*)p);
	if (len > UTF8MAXLEN){
		mCode[0] = 32;
	} else if (len == 0){
		mCode[0] = 32;
	} else {
		for (int i=0; i<len; i++){
			mCode[i] = p[i];
		}
	}
}

void UTF8SCHAR::setChar(const uint8_t* const p, bool p1, int p2, int p3){
	int len;
	
	for (int i=0; i<UTF8MAXLEN; i++)
		mCode[i] = 0;
	
	len = getFirstCharBytesU8(p);
	if (len > UTF8MAXLEN){
		mCode[0] = 32;
	} else if (len==0){
		mCode[0] = 32;
	}	else {
		for (int i=0; i<len; i++){
			mCode[i] = p[i];
		}
	}
	mValid = true;
	mUnderLine = p1;
	mFColor = p2;
	mBColor = p3;
}

int UTF8SCHAR::getDLen(){
	return getFirstDLenU8(mCode);
}

/*UTF8SCHAR& UTF8SCHAR::operator=(const UTF8SCHAR& p){
	mValid = p.mValid;
	mUnderLine = p.mUnderLine;
	mFColor = p.mFColor;
	mBColor = p.mBColor;
	for (int i=0; i<UTF8MAXLEN; i++) mCode[i] = p.mCode[i];
	return *this;
}*/

/*bool UTF8SCHAR::operator==(const SCHAR* rhs){
	bool result = true;
	
	for (int k=0; k<UTF8MAXLEN; k++){
		if (mCode[k]==0 || rhs->mCode[k]==0)
			break;
		if (mCode[k] != rhs->mCode[k]){
		  result = false;
			break;
		}
	}
	
	return result;
}*/

/* 依照字元本身的前景、背景顏色及是否有底線屬性印出字元 */
/* 呼叫者須自行控制游標位置 */
/* 列印後預設的前景、背景顏色及底線屬性會被修改成本字元所有屬性 */
/* 呼叫者須自行恢復預設的前景、背景顏色及底線屬性 */
void UTF8SCHAR::print(){
	char Buf[20];
	
	if (!mValid)
		return;
	
	if (mValid){
		if (mUnderLine)
			std::cout << "\x1B[4m";
	  else
			std::cout << "\x1B[24m";
		
	  sprintf(Buf, "\x1B[48;5;%dm", mBColor);
		std::cout << Buf;
		sprintf(Buf, "\x1B[38;5;%dm", mFColor);
	  std::cout << Buf << mCode;
	}
}

std::ostream& operator<<(std::ostream &s, UTF8SCHAR p){
	s << "\x1B[0m";
	for (int i=0; i<UTF8MAXLEN; i++)
	  s << (int)p.mCode[i] << " ";
  s << std::endl;
	return s;
}