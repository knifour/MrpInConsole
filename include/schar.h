#ifndef __SCHAR_H
#define __SCHAR_H

#include <attr.h>
#include <stdint.h>

#define MAXBYTES 7  // 定義字元編碼最長的byte stream數(含字串結束字元0)

class SCHAR {
protected:
  uint8_t mCode[MAXBYTES];
  bool mValid;
	bool mUnderLine;
	int mFColor;
	int mBColor;
	
public:
  SCHAR();
	bool isValid(void);
	void setValid(const bool);
	void setUnderLine(bool);
	void setFColor(int);
	void setBColor(int);
	int getFColor(void);
	int getBColor(void);
	
	// 運算子重載
	void operator=(const SCHAR& rhs);
	bool operator==(const SCHAR& rhs);
	
	// 純虛擬函數
	virtual void setChar(const uint8_t* const, bool, int, int) = 0;
	virtual int getDLen() = 0;
	virtual void print() = 0;
};

#endif