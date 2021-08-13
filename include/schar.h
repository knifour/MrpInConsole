#ifndef __SCHAR_H
#define __SCHAR_H

#include <attr.h>
#include <stdint.h>
#include <iostream>
#include <string>

#define __UNICODE_BMP

/*#ifdef __UNICODE_BMP
  // 如果定義了基本多文種平面(BMP)，表示只支援原始定義的Unicode文字(後來加入的Unicode字元都不支援)
	// 則將UTF8最大長度設定為4(含字串結束字元0)
  #define MAXBYTES 4
#else
  // 如果未定義基本文種平面的話將支援所有Unicode定義的文字
  // 則將UTF8最大長度設定為7(含字串結束字元0)
  #define MAXBYTES 7  
#endif*/

class SCHAR {
protected:
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
	bool isValid(void) const;
	// 設定此字元是否為有效螢幕字元
	void setValid(const bool);
	// 取得是否畫底線
	bool getUnderLine() const;
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
	int getFColor(void) const;
	// 取得背景色
	int getBColor(void) const;
	
	// 純虛擬函數
	// 運算子重載
	virtual SCHAR& operator=(const SCHAR& rhs) = 0;
	virtual bool operator==(const SCHAR& rhs) const = 0;
	
	virtual void setChar(const uint8_t*, bool, int, int) = 0;
	virtual std::string getChar() const = 0;
	virtual int getDisplayLength() const = 0;
	virtual void printMember() const = 0;
	virtual void printChar() const = 0;
	virtual bool isWide() const = 0;
};

#endif