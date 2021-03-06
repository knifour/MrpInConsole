#ifndef __TERMINAL_H
#define __TERMINAL_H

// 使用ioctl函式需使用此標頭檔
#include <sys/ioctl.h> 
// 有定義STDOUT_FILENO, 使用ioctl時會用到
#include <unistd.h> 
#include <string.h>
#include <attr.h>
#include <utf8schar.h>
#include <util.h>

using namespace std;

class TERMINAL{
private:
	// 取得Terminal列數及每列字數
	void getConsoleSize();                               

protected:
	// 終端機緩衝區
	UTF8SCHAR  **TermBuf;
	// 終端機緩衝區操作指標
	SCHAR *sp;
	// 終端機總列數、總行數
	int mLINS, mCOLS;
	// 目前所在列、行
	int mCurLin, mCurCol;
	// 儲存現有前景色、背景色	
	int mCurFColor, mCurBColor;  
	// 是否畫底線	
	bool mUnderLine;
	
	// 建立顯示緩衝區	
  void createBuffer(void);  
	// 終端機初始化，若未指定參數時預設為黑底、白字
	void init(int FColor=ATTR::WHITE, int BColor=ATTR::BLACK);     
	// 依照游標位置取得顯示緩衝區指標sp，左上角位置為1,1	
	bool setSP(int, int);                                          
	
public:
  // 無參數建構式
  TERMINAL();
	// 有參數建構式，可以指定前景色不指定背景色(此時背景色為黑色)
	TERMINAL(int FColor, int BColor=ATTR::BLACK);
	// 解構式
	~TERMINAL();
	// 重設所有屬性(包括顏色)
	void resetAttr(void);
	// 以顏色代碼設定前景色，顏色代碼超出範圍無效
	void setFColor(int);
	// 以RGB設定前景色，RGB值為0~5
	void setFColor(int, int, int);
	// 以顏色代碼設定背景色，顏色代碼超出範圍無效
	void setBColor(int);
	// 以RGB設定背景色，RGB值為0~5
	void setBColor(int, int, int);
	// 設定是否畫底線
	void setUnderLine(bool);
	// 取得終端機列數
	int getLINS();
	// 取得終端機行數
	int getCOLS();
	// 清除終端機
	void cls();
	// 設定游標位置(超出終端機範圍無效，且傳回false)
	void locate(int, int);
};

#endif