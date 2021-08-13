#ifndef __UTF8SCHAR_H
#define __UTF8SCHAR_H

#include <schar.h>
#include <stdio.h>
#include <iostream>
#include <util.h>
#include <utf8.h>

#ifdef __UNICODE_BMP
  // 如果定義了基本多文種平面(BMP)，表示只支援原始定義的Unicode文字(後來加入的Unicode字元都不支援)
	// 則將UTF8最大長度設定為4(含字串結束字元0)
  #define UTF8MAXLEN 4
#else
  // 如果未定義基本文種平面的話將支援所有Unicode定義的文字
  // 則將UTF8最大長度設定為7(含字串結束字元0)
  #define UTF8MAXLEN 7
#endif

using namespace std;
using namespace utf8;

class UTF8SCHAR : public SCHAR {
protected:
  // 字元編碼
	uint8_t mCode[UTF8MAXLEN];
	
public:
  UTF8SCHAR();
	UTF8SCHAR(int, int pBColor=0);
	UTF8SCHAR(const UTF8SCHAR& p);
	UTF8SCHAR(const char* p);
	UTF8SCHAR(const char* p, int, int pBColor=0);
	friend std::ostream& operator<<(std::ostream& s, UTF8SCHAR p);
	
	// 運算子重載
	SCHAR& operator=(const SCHAR& rhs) override;
	bool operator==(const SCHAR& rhs) const override;
	
	// 重載父類別虛擬函數
	void setChar(const uint8_t*, bool, int, int) override;
	std::string getChar() const override;
	int getDisplayLength() const override;
	void printMember() const override;
	void printChar() const override;
	bool isWide() const override;
};

#endif