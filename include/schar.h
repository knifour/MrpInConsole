#ifndef __SCHAR_H
#define __SCHAR_H

#include <attr.h>
#include <stdint.h>

class SCHAR {
protected:
  bool mValid;
	bool mUnderLine;
	int mFColor;
	int mBColor;
	
public:
  SCHAR();
	// bool operator==(const SCHAR &rhs);
	bool isValid(void);
	void setValid(const bool);
	void setUnderLine(bool);
	void setFColor(int);
	void setBColor(int);
	int getFColor(void);
	int getBColor(void);
	virtual bool operator==(const SCHAR* rhs) = 0;
	virtual void setChar(uint8_t const*, bool, int, int) = 0;
	virtual int getDLen() = 0;
	virtual void print() = 0;
};

#endif