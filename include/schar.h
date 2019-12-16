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
	/* ATTR mFColor;
	ATTR mBColor; */
	
public:
  SCHAR();
	bool operator==(const SCHAR &rhs);
	bool IsValid(void);
	void SetValid(const bool);
	/* void SetFColor(ATTR pFColor);
	void SetBColor(ATTR pBColor);
	ATTR GetFColor(void);
	ATTR GetBColor(void); */
	void SetUnderLine(bool);
	void SetFColor(int);
	void SetBColor(int);
	int GetFColor(void);
	int GetBColor(void);
	virtual void SetChar(uint8_t const *, bool, int, int) = 0;
	virtual int DLen() = 0;
	virtual void print() = 0;
};

#endif