/* 類別名稱TWINDOW表示為TERMINAL WINDOW之意，用以跟圖形WINDOW區別 */
/* 它是所有視窗相關類別的父類別 */

#ifndef __TWINDOW_H
#define __TWINDOW_H

#include <string>
#include <screen.h>

using namespace std;

/* 結構名稱TWS儲存視窗的基本資料，建立類別時必須先設定好視窗基本資料 */
/* TWINDOW的父視窗一定是SCREEN類別，所有TWINDOW類別沒有從屬關係 */
/* TWINDOW類別只有先後順序且儲存在父視窗SCREEN類別的twindow成員變數裡面 */
/* 先後順序主要在定義重繪時的先後順序(依照視窗建立順序) */
/* SCREEN的mTWincnt變數儲存TWINDOW類別總數 */
typedef struct {
	SCREEN *parant;     /* 儲存父視窗指標 */
	int lin, col;       /* 視窗左上角座標 */
	int LINS, COLS;     /* 視窗列數、行數 */
	int FColor, BColor; /* 視窗前景、背景色 */
	bool Board;         /* 是否有外框，有外框時視窗列數必須大於等於3，行數必須大於等於6 */
} TWS;

class TWINDOW{
public:
  TWINDOW(TWS);            /* 視窗建構函式 */
	~TWINDOW();

protected:
	TWS tws;                 /* 視窗基本資料結構 */
	bool mError;             /* 此值若為true，表示視窗的設定值嚴重錯誤，任何對視窗的操作都沒有作用 */
	bool mVisible;           /* 視窗是否顯示，預設為不顯示 */
	UTF8SCHAR **TWinBuf;     /* 視窗緩衝區 */
	SCHAR* sp;               /* 視窗字元操作指標 */
};

#endif