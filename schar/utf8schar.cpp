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
	
	// len = getFirstCharBytesU8((uint8_t*)p);
	len = getUtfLength((uint8_t)p[0]);
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

UTF8SCHAR::UTF8SCHAR(const char* p, int pFColor, int pBColor){
	int len;
	
	mFColor = pFColor;
	mBColor = pBColor;
	
	for (int i=0; i<UTF8MAXLEN; i++)
		mCode[i] = 0;
	
	len = getUtfLength((uint8_t)p[0]);
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

//void UTF8SCHAR::setChar(const uint8_t* p, bool p1, int p2, int p3){
void UTF8SCHAR::setChar(const char* p, bool p1, int p2, int p3){
	int len;
	
	for (int i=0; i<UTF8MAXLEN; i++)
		mCode[i] = 0;
	
	// len = getFirstCharBytesU8(p);
	len = getUtfLength((uint8_t)p[0]);
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

string UTF8SCHAR::getChar() const{
	return string((char*)mCode);
}

int UTF8SCHAR::getDisplayLength() const{
	return getFirstDisplayLength(mCode);
}

SCHAR& UTF8SCHAR::operator=(const SCHAR& rhs){
	mValid = rhs.isValid();
	mUnderLine = rhs.getUnderLine();
	mFColor = rhs.getFColor();
	mBColor = rhs.getBColor();
	const string buf = rhs.getChar();
	//for (int i=0; i<UTF8MAXLEN; i++) mCode[i] = (uint8_t)buf[i];
	for (int i=0; i<UTF8MAXLEN; i++) mCode[i] = buf[i];
	return *this;
}

bool UTF8SCHAR::operator==(const SCHAR& rhs) const{
	bool result = true;
	
	const string buf = rhs.getChar();
	for (int k=0; k<UTF8MAXLEN; k++){
		if (mCode[k]==0 || buf[k]==0)
			break;
		//if (mCode[k] != (uint8_t)buf[k]){
		if (mCode[k] != buf[k]){
		  result = false;
			break;
		}
	}
	
	return result;
}

void UTF8SCHAR::printMember() const {
	cout << "Valid:" << ((mValid) ? "true" : "false") << endl;
	cout << "UnderLine:" << ((mUnderLine) ? "true" : "false") << endl;
	cout << "FColor:" << mFColor << endl;
	cout << "BColor:" << mBColor << endl;
	for (int i=0; i<UTF8MAXLEN; i++)
	  printf("%02X ", mCode[i]);
	cout << endl << endl;
}

/* 依照字元本身的前景、背景顏色及是否有底線屬性印出字元 */
/* 呼叫者須自行控制游標位置 */
/* 列印後預設的前景、背景顏色及底線屬性會被修改成本字元所有屬性 */
/* 呼叫者須自行恢復預設的前景、背景顏色及底線屬性 */
void UTF8SCHAR::printChar() const {
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

/* 判斷該字元是否屬於寬字元 */
bool UTF8SCHAR::isWide() const{
	if (getFirstDisplayLength(mCode)==2)
		return true;
	else
		return false;
}

bool UTF8SCHAR::isWideTail() const {
	return !mValid;
}

std::ostream& operator<<(std::ostream &s, UTF8SCHAR p){
	char Buf[20];
	
	if (p.mValid){
		if (p.mUnderLine)
			cout << "\x1B[4m";
	  else
			cout << "\x1B[24m";
		
	  sprintf(Buf, "\x1B[48;5;%dm", p.mBColor);
		cout << Buf;
		sprintf(Buf, "\x1B[38;5;%dm", p.mFColor);
	  cout << Buf << p.mCode << "\x1B[0m";
	}
	
	return s;
}