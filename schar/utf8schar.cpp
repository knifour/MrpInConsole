#include <utf8schar.h>
#include <stdio.h>

UTF8SCHAR::UTF8SCHAR(){
	for (int k=0; k<UTF8MAXLEN; k++) Utf8[k] = 0;
}

UTF8SCHAR::UTF8SCHAR(ATTR pFColor, ATTR pBColor){
	mFColor = pFColor;
	mBColor = pBColor;
	for (int k=0; k<UTF8MAXLEN; k++) Utf8[k] = 0;
}

UTF8SCHAR::UTF8SCHAR(const UTF8SCHAR &p){
	mFColor = p.mFColor;
	mBColor = p.mBColor;
	for (int i=0; i<UTF8MAXLEN; i++) Utf8[i] = p.Utf8[i];
}

UTF8SCHAR::UTF8SCHAR(const char *p){
	for (int i=0; i<UTF8MAXLEN; i++){
		if (p[i] == 0){
			Utf8[i] = 0;
			break;
		}
		Utf8[i] = p[i];
	}
}

void UTF8SCHAR::SetChar(uint8_t const *p){
	int len;
	
	len = Utf8Len(p);
	if (len > UTF8MAXLEN)
		len = UTF8MAXLEN;
	if (len==0){
		for (int i=0; i<UTF8MAXLEN; i++){
			Utf8[i] = 0;
		}
		Utf8[0] = 32;
	}
	else {
		for (int i=0; i<len; i++){
			Utf8[i] = p[i];
		}
		Utf8[len] = 0;
	}
	mValid = true;
}

int UTF8SCHAR::DLen(){
	return Utf8DLen(Utf8);
}

UTF8SCHAR& UTF8SCHAR::operator=(const UTF8SCHAR &p){
	mValid = p.mValid;
	mFColor = p.mFColor;
	mBColor = p.mBColor;
	for (int i=0; i<UTF8MAXLEN; i++) Utf8[i] = p.Utf8[i];
	return *this;
}

/* 依照字元本身的前景、背景顏色印出字元 */
/* 呼叫者須自行控制游標位置 */
/* 列印後預設的前景、背景顏色會被修改成本字元的顏色 */
/* 呼叫者須自行恢復預設的前景、背景顏色 */
void UTF8SCHAR::print(){
	char Buf[20];
	if (mValid){
	  sprintf(Buf, "\x1B[%d;%dm", (int)mFColor, (int)mBColor);
	  std::cout << Buf << Utf8;
	}
}

std::ostream& operator<<(std::ostream &s, UTF8SCHAR p){
	s << p.Utf8;
	return s;
}