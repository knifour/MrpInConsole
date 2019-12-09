#ifndef __SCHAR_H
#define __SCHAR_H

#include <attr.h>
#include <stdint.h>

class SCHAR {
protected:
  bool mValid;
	ATTR mFColor;
	ATTR mBColor;
	
public:
  SCHAR();
	bool operator==(const SCHAR &rhs);
	bool IsValid(void);
	void SetValid(const bool);
	void SetFColor(ATTR pFColor);
	void SetBColor(ATTR pBColor);
	ATTR GetFColor(void);
	ATTR GetBColor(void);
	virtual void SetChar(uint8_t const *p) = 0;
	virtual int DLen() = 0;
	virtual void print() = 0;
};

#endif