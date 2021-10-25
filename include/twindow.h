/* 類別名稱TWINDOW表示為TERMINAL WINDOW之意，用以跟圖形WINDOW區別 */
/* 它是所有視窗相關類別的父類別 */

#ifndef __TWINDOW_H
#define __TWINDOW_H

#include <string>
#include <stdarg.h>
#include <attr.h>
#include <schar.h>
#include <terminal.h>

using namespace std;

template <class T>
class TWINDOW{
protected:
  /* 父視窗指標, nullptr代表沒有父視窗 */
  TWINDOW* mParant;
	/* 視窗左上角位置 */
  int mLin, mCol;
	/* 視窗列數、行數 */
	int mLINS, mCOLS;
  /* 視窗前景色、背景色 */	
	int mFColor, mBColor;
	/* 此值若為true，表示視窗的設定值嚴重錯誤，任何對視窗的操作都沒有作用 */
	bool mError;
	/* 是否畫底線 */
	bool mUnderline;
  /* 視窗緩衝區 */	
	T **TWindowBuf;
  /* 視窗字元操作指標 */	
	SCHAR* sp;

  /* 建立視窗緩衝區 */
	void createBuffer(void);	
	
public:
	TWINDOW();
	/* 第二個參數為字串，字串格式為"llcccLLCCC"，字串內容皆為數字 */
	/* ll：左上角行座標(不足位數須補0)，ccc：左上角列座標 */
	/* LL：視窗總行數(可省略，須在程式後面自行設定)，CCC：視窗寬度(可省略) */
  TWINDOW(TWINDOW*, const char *);
	~TWINDOW();
};

#endif