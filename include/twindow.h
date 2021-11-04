/* 類別名稱TWINDOW表示為TERMINAL WINDOW之意，用以跟圖形WINDOW區別 */
/* 它是所有視窗相關類別的父類別 */

#ifndef __TWINDOW_H
#define __TWINDOW_H

#include <string>
#include <attr.h>
#include <utf8.h>
#include <utf8schar.h>
#include <terminal.h>
#include <list>

using namespace std;

typedef struct tagWIN {
	int Lin;
	int Col;
	int Lins;
	int Cols;
} WIN;

template <class T>
class TWINDOW{
protected:
  /* TERMINAL指標，表示此視窗是建立在哪個TERMINAL上面 */
	TERMINAL<T>* mTerminal;
  /* 父視窗指標, nullptr代表沒有父視窗 */
  TWINDOW* mParant;
	/* 子視窗 */
	list<TWINDOW*> mChild;
	/* 視窗左上角位置 */
  int mLin, mCol;
	/* 現在游標位置 */
	int mCurLin, mCurCol;
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
	// 視窗初始化，若未指定參數時預設為黑底、白字
	void init(int FColor=ATTR::WHITE, int BColor=ATTR::BLACK); 
	// 依照游標位置取得顯示緩衝區指標sp，左上角位置為1,1
	bool setSP(int, int);
	// 根據WIN struct設定的游標位置及列數、行數將視窗緩衝區的資料移動到TERMINAL緩衝區且即時顯示出來
	//void TWin2Term(WIN);
	
public:
  void TWin2Term(WIN);
	TWINDOW();
	~TWINDOW();
	// 重設所有屬性(包括顏色)
	void resetAttr(void);
	// 以顏色代碼設定前景色，顏色代碼超出範圍無效
	void setFColor(int);
	// 以RGB設定前景色，RGB值為0~5
	void setFColor(int, int, int);
	// 取得前景色
	int getFColor(void) const;
	// 以顏色代碼設定背景色，顏色代碼超出範圍無效
	void setBColor(int);
	// 以RGB設定背景色，RGB值為0~5
	void setBColor(int, int, int);
	// 取得背景色
	int getBColor(void) const;
	// 設定是否畫底線
	void setUnderline(bool);
	// 取得是否底線設定
	bool getUnderline(void) const;
	// 取得視窗列數
	int getLINS() const;
	// 取得視窗行數
	int getCOLS() const;
	// 取得游標所在列
	int getCurLin() const;
	// 取得游標所在行
	int getCurCol() const;
	// 清除視窗
	void cls();
	// 設定游標位置(超出視窗範圍無效)，視窗左上角位置為1, 1
	void locate(int, int);
};

#endif