#include <iostream>
#include <stdio.h>
#include <twindow.h>

template<class T> TWINDOW<T>::TWINDOW(){
	mTerminal = nullptr;
	mParant = nullptr;
  mLin = mCol = 1;
  mLINS = 0;
  mCOLS = 0;	
	mFColor = ATTR::WHITE;
	mBColor = ATTR::BLACK;
	mUnderline = false;
	mError = true;
}

template<class T> void TWINDOW<T>::createBuffer(void){
	if (mError)
		return;
	
	if (mLINS<1){
		mError = true;
		return;
	}
	
	if (mCOLS<1){
		mError = true;
		return;
	}
  
	TWindowBuf = new T*[mLINS];
	for (int i=0; i<mLINS; i++)
		TWindowBuf[i] = new T[mCOLS];
}

template<class T> void TWINDOW<T>::TWin2Term(WIN sWin, int tLin, int tCol){
	if (mError)
		return;
	
	if (mTerminal==nullptr)
		return;
	
	// 來源列座標超出視窗位置無效
	if (sWin.Lin < 1 || sWin.Lin > mLINS)
		return;
	
	// 來源行座標超出視窗位置無效
	if (sWin.Col < 1 || sWin.Col > mCOLS)
		return;
	
	int LINS = mTerminal->getLINS();
	int COLS = mTerminal->getCOLS();
	
	// 視窗座標對應到TERMINAL座標
	int realLin = mLin + sWin.Lin - 1;
	if (realLin < 1 || realLin > LINS)
		return;
	int realCol = mCol + sWin.Col - 1;
	if (realCol < 1 || realCol > COLS)
		return;
	
	// 目的列座標超出TERMINAL位置無效
	if (tLin < 1 || tLin > LINS)
		return;
	
	// 目的行座標超出TERMINAL位置無效
	if (tCol < 1 || tCol > COLS)
		return;
	
	// 計算來源視窗右下角座標
	int sBottom = sWin.Lin + sWin.Lins - 1;
	if (sBottom > mLINS)
		sBottom = mLINS;
	int sRight = sWin.Col + sWin.Cols - 1;
	if (sRight > mCOLS)
		sRight = mCOLS;
	
	int tmpLin = realLin - 1;
	int tmpCol;
	for (int i=sWin.Lin; i<=sBottom; i++){
		tmpLin++;
		if (tmpLin > LINS)
			break;
		tmpCol = realCol - 1;
		for (int j=sWin.Col; j<=sRight; j++){
		 tmpCol++;
		 if (tmpCol > COLS)
			 break;
		 if (setSP(i, j))
		   mTerminal->setSchar(tmpLin, tmpCol, sp);
		}
	}
	
	mTerminal->reflash(realLin, realCol, sWin.Lins, sWin.Cols);
}

template<class T> bool TWINDOW<T>::setSP(int pLin, int pCol){
	int lin, col;
	
	if (pLin < 1 || pLin > mLINS)
		return false;
	
	if (pCol < 1 || pCol > mCOLS)
		return false;
	
	lin = pLin - 1;
	col = pCol - 1;
	sp = &TWindowBuf[lin][col];
	return true;
}

template<class T> TWINDOW<T>::~TWINDOW(){
	for (int i=0; i<mLINS; i++)
		delete[] TWindowBuf[i];
	
	delete[] TWindowBuf;
}

template class TWINDOW<UTF8SCHAR>;