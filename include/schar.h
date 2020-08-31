#ifndef __SCHAR_H
#define __SCHAR_H

#include <attr.h>
#include <stdint.h>

// 定義螢幕字元編碼最長的byte stream數(含字串結束字元0)
#define MAXBYTES 7  

class SCHAR {
protected:
	// 儲存螢幕字元編碼
  uint8_t mCode[MAXBYTES];
	// 螢幕字元是否有效(通常是寬字元的下一字)
  bool mValid;
	// 是否畫底線
	bool mUnderLine;
	// 前景色
	int mFColor;
	// 背景色
	int mBColor;
	
public:
	// 無參數建構式
  SCHAR();
	// 是否為有效螢幕字元
	bool isValid(void);
	// 設定此字元是否為有效螢幕字元
	void setValid(const bool);
	// 設定是否畫底線
	void setUnderLine(bool);
	// 以顏色代碼設定前景色，顏色代碼超出範圍無效
	void setFColor(int);
	// 以RGB設定前景色，RGB值為0~5
	void setFColor(int, int, int);
	// 以顏色代碼設定背景色，顏色代碼超出範圍無效
	void setBColor(int);
	// 以RGB設定前景色，RGB值為0~5
	void setBColor(int, int, int);
	// 取得前景色
	int getFColor(void);
	// 取得背景色
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