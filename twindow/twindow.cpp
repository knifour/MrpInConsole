#include <iostream>
#include <stdio.h>
#include <twindow.h>

template<class T> TWINDOW<T>::TWINDOW(){
	mTerminal = nullptr;
	mParant = nullptr;
  mLin = mCol = 1;
	mCurLin = mCurCol = 1;
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

template<class T> void TWINDOW<T>::TWin2Term(WIN sWin){
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

template<class T> void TWINDOW<T>::init(int FColor, int BColor){
	uint8_t blank[] = " ";
	
	if (mError)
		return;
	
	setFColor(FColor);
	setBColor(BColor);
	setUnderline(false);
	
	for (int i=1; i<=mLINS; i++)
		for (int j=1; j<=mCOLS; j++){
			if (setSP(i, j)){
			  sp->setChar(blank, mUnderline, mFColor, mBColor);
			}
		}
	
	WIN win;
	
	win.Lin = win.Col = 1;
	win.Lins = mLINS;
	win.Cols = mCOLS;
	TWin2Term(win);
}

template<class T> bool TWINDOW<T>::setSP(int pLin, int pCol){
	int lin, col;
	
	if (mError)
		return false;
	
	if (pLin < 1 || pLin > mLINS)
		return false;
	
	if (pCol < 1 || pCol > mCOLS)
		return false;
	
	lin = pLin - 1;
	col = pCol - 1;
	sp = &TWindowBuf[lin][col];
	return true;
}

template<class T> void TWINDOW<T>::resetAttr(void){
	cout << "\x1B[0m";
	mUnderline = false;
	mFColor = ATTR::WHITE;
	mBColor = ATTR::BLACK;
}

template<class T> void TWINDOW<T>::setFColor(int p){
	if (p >= 0 && p <= 255)
	  mFColor = p;
}

template<class T> void TWINDOW<T>::setFColor(int r, int g, int b){
	setFColor(16 + r*36 + g*6 + b);
}

template<class T> int TWINDOW<T>::getFColor(void) const{
	return mFColor;
}

template<class T> void TWINDOW<T>::setBColor(int p){
	if (p >= 0 && p <= 255)
	  mBColor = p;
}

template<class T> void TWINDOW<T>::setBColor(int r, int g, int b){
	setBColor(16 + r*36 + g*6 + b);
}

template<class T> int TWINDOW<T>::getBColor(void) const{
	return mBColor;
}

template<class T> void TWINDOW<T>::setUnderline(bool p){
	mUnderline = p;
}

template<class T> bool TWINDOW<T>::getUnderline(void) const{
	return mUnderline;
}

template<class T> int TWINDOW<T>::getLINS() const{
	return mLINS;
}

template<class T> int TWINDOW<T>::getCOLS() const{
	return mCOLS;
}

template<class T> int TWINDOW<T>::getCurLin() const{
	return mCurLin;
}

template<class T> int TWINDOW<T>::getCurCol() const{
	return mCurCol;
}

template<class T> void TWINDOW<T>::cls(void){
	/*init(mFColor, mBColor);*/
	init(mFColor, mBColor);
	locate(1, 1);
}

template<class T> void TWINDOW<T>::locate(int pLin, int pCol){
	char buf[1024];
	char buf2[30];
	char *ap=buf2;
	char *gotostr;
	
	if (pLin < 1 || pLin > mLINS) 
		return;
	if (pCol < 1 || pCol > mCOLS)
		return;
	int tLin = mLin + pLin - 1;
	if (tLin > mTerminal->getLINS())
		return;
	int tCol = mCol + pCol - 1;
	if (tCol > mTerminal->getCOLS())
		return;
	mCurLin = tLin;
	mCurCol = tCol;
	/*sprintf(Buf, "\x1B[%d;%dH", mCurLin, mCurCol);
	cout << Buf;*/
	tgetent(buf, getenv("TERM"));
	gotostr = tgetstr("cm", &ap);
	fputs(tgoto(gotostr, mCurCol-1, mCurLin-1), stdout);
}

template<class T> TWINDOW<T>::~TWINDOW(){
	for (int i=0; i<mLINS; i++)
		delete[] TWindowBuf[i];
	
	delete[] TWindowBuf;
}

template class TWINDOW<UTF8SCHAR>;