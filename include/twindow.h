/* 類別名稱TWINDOW表示為TERMINAL WINDOW之意，用以跟圖形WINDOW區別 */
/* 它是所有視窗相關類別的父類別 */

#ifndef __TWINDOW_H
#define __TWINDOW_H

#include <string>
#include <attr.h>
#include <utf8schar.h>
#include <terminal.h>

using namespace std;

template <class T>
class TWINDOW{
protected:
  /* TERMINAL指標，表示此視窗是建立在哪個TERMINAL上面 */
	TERMINAL<T>* mTerminal;
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
	void TWin2Term(WIN, int, int);
	bool setSP(int, int);
	
public:
	TWINDOW();
	~TWINDOW();
};

#endif