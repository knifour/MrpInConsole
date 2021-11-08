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

template<class T> void TWINDOW<T>::setSchar(int pLin, int pCol, SCHAR* pSchar){
	if (pLin < 1 || pLin > mLINS)
		return;
	
	if (pCol < 1 || pCol > mCOLS)
		return;
	
	if (setSP(pLin, pCol))
		*sp = *pSchar;
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
	char buf[30];
	/*char buf2[30];
	char *ap=buf2;
	char *gotostr;*/
	
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
	sprintf(buf, "\x1B[%d;%dH", mCurLin, mCurCol);
	cout << buf;
	/*tgetent(buf, getenv("TERM"));
	gotostr = tgetstr("cm", &ap);
	fputs(tgoto(gotostr, mCurCol-1, mCurLin-1), stdout);*/
}

template<class T> void TWINDOW<T>::print(const string p){
	print((uint8_t*)p.c_str());
}

template<class T> void TWINDOW<T>::print(const char* p){
	print((uint8_t*)p);
}

template<class T> void TWINDOW<T>::print(const uint8_t* p){
	int cnt, len, dlen;
	int maxlen;
	uint8_t blank[]=" ";
	
	// 字串含有不合法UTF8字元，則不列印結束
	if ((cnt=countChars(p))<0)
		return;
	
	dlen = getDisplayLength(p);
	maxlen = getCOLS() - mCurCol + 1;
	if (dlen > maxlen)
		dlen = maxlen;
	
	T* buf = new T[dlen+2];
	buf[0].setChar(blank, mUnderline, mFColor, mBColor);
	buf[dlen+1].setChar(blank, mUnderline, mFColor, mBColor);
	
	int strPos = 1;  // 要填入視窗顯示緩衝區的陣列起始位置
	int endPos = 0;  // 要填入視窗顯示緩衝區的陣列結束位置
	int curPos = 1;  // 將要列印的字串一個一個取出放入陣列，這個指標儲存著現在要填入的陣列位置
	int tmpLen = dlen;  // tmpLen儲存剩餘顯示寬度
	int strCol = mCurCol, tmpCol = mCurCol - 1; // tmpCol儲存列印後游標位置(最後一個字元所在位置)
	uint8_t tmp[3];
	
  if (setSP(mCurLin, mCurCol)){
		if (sp->isWideTail()){
			strCol--;  // 起始列印游標位置減1
			strPos--;  // 緩衝起始陣列位置減1
		}
	}
	
	for (int i=1; i<=cnt; i++){
		getMidStr(p, tmp, i, 1);  // 一次取出一個要顯示的字元放在tmp(寬字元、單字元皆算一個字元)
		len = getFirstDisplayLength(tmp); // 計算顯示寬度
		switch(len){
		case 2:
		  if (tmpLen == 1){  // 如果要顯示的字元寬度是2，但剩餘顯示寬度剩1
				buf[curPos].setChar(blank, mUnderline, mFColor, mBColor); // 因為只剩一格可顯示，所以在此位置填入空白
                                                                  // 避免要顯示內容超出視窗邊界
				endPos++;
				curPos++;
				tmpCol++;
			} else {
				buf[curPos].setChar(tmp, mUnderline, mFColor, mBColor);
				curPos++;
				buf[curPos].setValid(false);
				curPos++;
				endPos = endPos + 2;
				tmpCol = tmpCol + 2;
			}
		  break;
		case 1:
		  buf[curPos].setChar(tmp, mUnderline, mFColor, mBColor);
			endPos++;
			curPos++;
			tmpCol++;
		  break;
		};
		tmpLen = tmpLen - len;
		if (tmpLen<0)  // 如果剩餘顯示寬度小於0表示剩餘空格剩1格，但是要列印的字元有兩格
		  break;
	}
	
	// 結束後判斷最後一個字元是否位於寬字元的開頭
	if (setSP(mCurLin, tmpCol)){
		if (sp->isWide()){
			tmpCol++;  // 結束列印的游標位置加1
			endPos++;  // 緩衝區結束陣列位置加1
		}
	}
	
	SCHAR* tmpSP;
	tmpCol = strCol;
	for (int i=strPos; i<=endPos; i++){
		tmpSP = &buf[i];
		if (setSP(mCurLin, tmpCol)){
			*sp = *tmpSP;
			tmpCol++;
		}
	}
	
	WIN win;
	
	win.Lin = mCurLin;
	win.Lins = 1;
	win.Col = strCol;
	win.Cols = dlen;
	
	TWin2Term(win);
	
	delete[] buf;
}

template<class T> TWINDOW<T>::~TWINDOW(){
	for (int i=0; i<mLINS; i++)
		delete[] TWindowBuf[i];
	
	delete[] TWindowBuf;
}

template class TWINDOW<UTF8SCHAR>;