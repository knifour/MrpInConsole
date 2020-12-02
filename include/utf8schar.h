#ifndef __UTF8SCHAR_H
#define __UTF8SCHAR_H

#include <schar.h>
#include <iostream>
#include <util.h>
#include <utf8.h>

#define UTF8MAXLEN 7

using namespace utf8;

class UTF8SCHAR : public SCHAR {
public:
  UTF8SCHAR();
	UTF8SCHAR(int pFColor, int pBColor=0);
	UTF8SCHAR(const UTF8SCHAR& p);
	UTF8SCHAR(const char* p);
	friend std::ostream& operator<<(std::ostream& s, UTF8SCHAR p);
	
	// 重載父類別虛擬函數
	void setChar(const uint8_t*, bool, int, int) override;
	int getDLen() override;
	void print() override;
};

#endif