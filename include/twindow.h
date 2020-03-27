/* 類別名稱TWINDOW表示為TERMINAL WINDOW之意，用以跟圖形WINDOW區別 */
/* 它是所有視窗相關類別的父類別 */

#ifndef __TWINDOW_H
#define __TWINDOW_H

#include <string>
#include <stdarg.h>
#include <attr.h>
#include <screen.h>

using namespace std;

class TWINDOW{
public:
  /* 視窗建構函示：建構函示採用不定長度引數 */
	/* 第一個參數是父視窗指標，這個參數如果是null將導致視窗無效，任何對視窗的操作都將無效 */
	/* 第二個參數是一個常數格式字串，用來描述後面不定數量參數的意義及數量 */
	/* 格式字串說明如下 */
	/* 'l' -> 左上角列座標, 'c' -> 左上角行座標 */
	/* 'L' -> 視窗總列數, 'C' -> 視窗總行數 */
	/* 'F' -> 視窗前景色, 'B' -> 視窗背景色 */
	friend class TWMGR;
	TWINDOW();
  TWINDOW(SCREEN*, const char *, ...);
	~TWINDOW();

protected:
  SCREEN *mParant;         /* 父視窗指標 */
  int mLin, mCol;          /* 視窗左上角位置 */
	int mLINS, mCOLS;        /* 視窗列數、行數 */
	int mFColor, mBColor;    /* 視窗前景色、背景色 */
	bool mError;             /* 此值若為true，表示視窗的設定值嚴重錯誤，任何對視窗的操作都沒有作用 */
	bool mVisible;           /* 視窗是否顯示，預設為不顯示 */
	UTF8SCHAR **TWinBuf;     /* 視窗緩衝區 */
	SCHAR* sp;               /* 視窗字元操作指標 */
};

#endif