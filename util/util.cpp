#include <iostream>
#include <termios.h>
#include <stdio.h>
#include <util.h>

static struct termios old, current;

void initTermios(int echo){
	tcgetattr(0, &old);
	current = old;
	current.c_lflag &= !ICANON;
	if (echo){
		current.c_lflag &= ~ECHO;
	}
	tcsetattr(0, TCSANOW, &current);
}

void resetTermios(void){
	tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo){
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

/* 模擬Windows的getch()函數，按鍵不會顯示在終端機上面 */
char getch(void){
	return getch_(0);
}

/* 模擬Windows的getch()函數，按鍵會顯示在終端機上面 */
char getche(void){
	return getch_(1);
}

void showCursor(void){
  std::cout << "\x1B[?25h";  // 顯示游標
}

void hideCursor(void){
	std::cout << "\x1B[?25l";  // 隱藏游標
}

void getCursorPos(int& lin, int& col){  // 取得游標位置
	char buf[10];
	char ch;
	int cnt = 0;
	int tl = 0, tc = 0;
	
	std::cout << "\x1B[6n";  // 送出這個訊號之後，會由標準輸入傳回 ESC[y;xR 的訊號
	                         // 其中y值就是游標所在列，x值就是游標所在行
	while ((ch=getch()) != 'R'){
		buf[cnt] = ch;
		cnt++;
	}
	buf[cnt] = 0;
	cnt = 2;
	while (buf[cnt] != ';'){
		tl = tl * 10 + (buf[cnt]-48);
		cnt++;
	}
	cnt++;
	while (buf[cnt] != 0){
		tc = tc * 10 + (buf[cnt]-48);
		cnt++;
	}
	lin = tl;
	col = tc;
}

/* 等待輸入，然後傳回輸入字元 */
/* 如果輸入特殊按鍵，特殊鍵代碼將藉由key傳回 */
/* 偵測到使用者案特殊鍵時，回傳的字元代碼為0，可由字元代碼是否為0判斷使用者是否按了特殊鍵 */
/* 按鍵定義在keypad.h */
char input(int &key){
	bool esc = false;
	char ch;
	int result;
	int cnt = 0;
	
	while (1){
		ch = getch();
		if (ch == ESC){
			if (esc){
				key = ESC;
				return 0;
			}
			esc = true;
			cnt++;
			continue;
		}
		if (esc){
			switch (cnt){
			case 1:
			  if (ch == FUNCKEY || ch == PADKEY){
					cnt++;
					continue;
				} else {
					break;
				}
			case 2:
			  if (ch >= HOME && ch <= PAGEDOWN){
					cnt++;
					key = ch;
					continue;
				} else if ((ch >= KEY_UP && ch <= KEYPAD5) || (ch >= KEY_F1 && ch <= KEY_F12)){
					key = ch;
					return 0;
				}
				break;
			case 3:
			  if (ch == 126){
					return 0;
				}
				break;
			}
		}
		if ((ch >= 1 && ch <= 31) || ch == BACKSPACE){
			key = ch;
			return 0;
		}
		cnt = 0;
		esc = false;
		key = 0;
		return ch;
	}
}

/* 傳入西元年份，判斷該年是不是閏年 */
bool isLeap(int year){
	return (year % 400 == 0) ? true  :
	       (year % 100 == 0) ? false :
	       (year %   4 == 0) ? true  : false;
}

/* 動態二維陣列 */
/* 使用者以指指標接收回傳的指標值 */
/* 使用者必須自行釋放函式配置的記憶體 */
void* new2D(int h, int w, int size){
	int i;
	void **p;
	
	p = (void**)new char[h*sizeof(void*) + h*w*size];
	for (i=0; i < h; i++)
		p[i] = ((char*)(p+h)) + i*w*size;
	
  return p;
}

int getFirstCharBytesU8(const std::string& utf8){
	uint8_t first_byte = (uint8_t)utf8[0];
	int len = getUtfLengthU8(first_byte);
	
	return len;
}

int getFirstCharBytesU8(const uint8_t* utf8){
	uint8_t first_byte = utf8[0];
	int len = getUtfLengthU8(first_byte);
	
	return len;
}

int getFirstCharBytesU8(char first_byte){
	int len = getUtfLengthU8((uint8_t)first_byte);
	
	return len;
}

int getUtfLengthU8(uint8_t first_byte){
	return (first_byte >> 7)   == 0    ? 1 :
		     (first_byte & 0xFC) == 0xFC ? 6 :
		     (first_byte & 0xF8) == 0xF8 ? 5 :
		     (first_byte & 0xF0) == 0xF0 ? 4 :
		     (first_byte & 0xE0) == 0xE0 ? 3 :
		     (first_byte & 0xC0) == 0xC0 ? 2 : 0;
}

int getFirstDLenU8(const std::string& utf8){
	uint32_t unicode = 0;
	uint8_t first_byte = (uint8_t)utf8[0];
	int len = getUtfLengthU8(first_byte);
	
	unicode += (uint8_t)(first_byte << len) >> len;
	for (uint8_t i=1; i<len; i++){
		unicode <<= 6;
		unicode += ((uint8_t)utf8[i]) & 0x3F;
	}

  return isWideChar(unicode) ? 2 : 1;	
}

int getFirstDLenU8(const uint8_t* utf8){
	uint32_t unicode = 0;
	uint8_t first_byte = utf8[0];
	int len = getUtfLengthU8(first_byte);
	
	unicode += (uint8_t)(first_byte << len) >> len;
	for (uint8_t i=1; i<len; i++){
		unicode <<= 6;
		unicode += (utf8[i]) & 0x3F;
	}
	
	return isWideChar(unicode) ? 2 : 1;
}

bool isWideChar(uint32_t unicode){
	return (unicode >= SEC0_LOW && unicode <= SEC0_HIGH) ? true :
	       (unicode >= SEC1_LOW && unicode <= SEC1_HIGH) ? true :
				 (unicode >= SEC2_LOW && unicode <= SEC2_HIGH) ? true :
				 (unicode >= SEC3_LOW && unicode <= SEC3_HIGH) ? true :
				 (unicode >= SEC4_LOW && unicode <= SEC4_HIGH) ? true :
				 (unicode >= SEC5_LOW && unicode <= SEC5_HIGH) ? true :
				 (unicode >= SEC6_LOW && unicode <= SEC6_HIGH) ? true :
				 (unicode >= SEC7_LOW && unicode <= SEC7_HIGH) ? true :
				 (unicode >= SEC8_LOW && unicode <= SEC8_HIGH) ? true : false;
}

int FromUtf8(std::string const &utf8, char *buf){
	int len;
	
	len = getFirstCharBytesU8(utf8);
	for (int i=0; i<len; i++){
		buf[i] = (char)utf8[i];
	}
	buf[len] = 0;
	
	return len;
}

int getCharsU8(uint8_t const *utf8){
	int result = 0;
	int len;
	int i = 0;
	
	while (utf8[i] != 0){
		len = getFirstCharBytesU8(utf8[i]);
		result = result + 1;
		i = i + len;
	}
	
	return result;
}

int getCharsU8(std::string const &utf8){
	int result = 0;
	int len;
	int i = 0;
	
	while (utf8[i] != 0){
		len = getFirstCharBytesU8(utf8[i]);
		result = result + 1;
		i = i + len;
	}
	
	return result;
}

int getDLenU8(uint8_t const *utf8){
	int result = 0;
	int len, dlen;
	int i = 0;
	
	while (utf8[i] != 0){
		len = getFirstCharBytesU8(utf8[i]);
		dlen = getFirstDLenU8(&utf8[i]);
		result = result + dlen;
		i = i + len;
	}
	
	return result;
}

int getDLenU8(std::string const &utf8){
	int result = 0;
	int len, dlen;
	int i = 0;
	
	while (utf8[i] != 0){
		len = getFirstCharBytesU8(utf8[i]);
		dlen = getFirstDLenU8((uint8_t*)&utf8[i]);
		result = result + dlen;
		i = i + len;
	}
	
	return result;
}

int Utf8Mid(uint8_t const *utf8, uint8_t *buf, int start, int length){
	int rlen = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0){
		buf[bps] = 0;
		return rlen;
	}
	
	if (length <= 0){
		buf[bps] = 0;
		return rlen;
	}
	
	rlen = getCharsU8(utf8);
	if (start > rlen){
		buf[bps] = 0;
		return rlen;
	}
	
	rlen = 1;
	while (rlen < start){
		len = getFirstCharBytesU8(utf8[ps]);
		ps = ps + len;
		rlen = rlen + 1;
	}
	
	rlen = 0;
	while (utf8[ps] != 0){
		len = getFirstCharBytesU8(utf8[ps]);
		for (int i=0; i<len; i++){
			buf[bps] = utf8[ps];
			ps++;
			bps++;
		}
		rlen = rlen + 1;
		if (rlen >= length){
			break;
		}
	}
	buf[bps] = 0;
	
	return rlen;
}

std::string Utf8Mids(uint8_t const *utf8, int start, int length){
	uint8_t buf[500];
	int rlen = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0){
		buf[bps] = 0;
		return std::string("");
	}
	
	if (length <= 0){
		buf[bps] = 0;
		return std::string("");
	}
	
	rlen = getCharsU8(utf8);
	if (start > rlen){
		buf[bps] = 0;
		return std::string("");
	}
	
	rlen = 1;
	while (rlen < start){
		len = getFirstCharBytesU8(utf8[ps]);
		ps = ps + len;
		rlen = rlen + 1;
	}
	
	rlen = 0;
	while (utf8[ps] != 0){
		len = getFirstCharBytesU8(utf8[ps]);
		for (int i=0; i<len; i++){
			buf[bps] = utf8[ps];
			ps++;
			bps++;
		}
		rlen = rlen + 1;
		if (rlen >= length){
			break;
		}
	}
	buf[bps] = 0;
	
	return std::string((char*)buf);
}

std::string convertBig5toUtf8(char *src, int *status){
	char *InBuf, *OutBuf;
	char *TmpInBuf, *TmpOutBuf;
	iconv_t cd;
	size_t SrcLen, DstLen, Ret;
	
	*status = 0; /* 回傳值為0表示正確完成工作 */
	if (src == NULL){
		*status = 1; /* 回傳值為1代表原始字串為NULL */
		return std::string(""); /* 回傳空字串 */
	}
	
	SrcLen = strlen(src);
	DstLen = SrcLen * 6 + 1;
	SrcLen = SrcLen + 1;
	if ((InBuf=(char*)malloc(SrcLen))==0){
		*status = 2; /* 回傳值為2代表記憶體配置失敗 */
		return std::string(""); /* 回傳空字串 */
	}
	
	if ((OutBuf=(char*)malloc(DstLen))==0){
		*status = 2; /* 回傳值為2代表記憶體配置失敗 */
		free(InBuf);
		return std::string(""); /* 回傳空字串 */
	}
	strcpy(InBuf, src);
	TmpInBuf = InBuf;
	TmpOutBuf = OutBuf;
	cd = iconv_open("utf8", "big5");
	if (cd == (iconv_t)-1){
		*status = 3; /* 回傳值為3代表轉碼初始化失敗 */
		free(InBuf);
		free(OutBuf);
		return std::string(""); /* 回傳空字串 */
	}
	
	Ret = iconv(cd, &TmpInBuf, &SrcLen, &TmpOutBuf, &DstLen);
	if (Ret == -1){
		*status = 4; /* 回傳值為4代表轉碼失敗 */
		free(InBuf);
		free(OutBuf);
		iconv_close(cd);
		return std::string(""); /* 回傳空字串 */
	}
	
	std::string result(OutBuf);
	free(InBuf);
	free(OutBuf);
	iconv_close(cd);
	return result;
}

std::string convertBig5toUtf8(std::string src, int *status){
	const char *tmp = src.c_str();
	return convertBig5toUtf8((char *)tmp, status);
}