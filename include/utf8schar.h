#ifndef __UTF8SCHAR_H
#define __UTF8SCHAR_H

#include <schar.h>
#include <iostream>
#include <util.h>

#define UTF8MAXLEN 7

class UTF8SCHAR : public SCHAR {
public:
  UTF8SCHAR();
	/* UTF8SCHAR(ATTR pFColor, ATTR pBColor=ATTR::BBlack); */
	UTF8SCHAR(int pFColor, int pBColor=0);
	UTF8SCHAR(const UTF8SCHAR& p);
	UTF8SCHAR(const char* p);
	void setChar(uint8_t const*, bool, int, int) override;
	int getDLen() override;
	UTF8SCHAR& operator=(const UTF8SCHAR& p);
	bool operator==(const SCHAR* rhs) override;
	friend std::ostream& operator<<(std::ostream& s, UTF8SCHAR p);
	void print() override;

private:	
	uint8_t Utf8[UTF8MAXLEN];
};

#endif