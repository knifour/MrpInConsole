#include <terminal.h>

template<class T>TERMINAL<T>::TERMINAL(){
	getConsoleSize();
	createBuffer();
  init();
}

template<class T>TERMINAL<T>::TERMINAL(int FColor, int BColor){
	getConsoleSize();
	createBuffer();
  init(FColor, BColor);	
}

// 重設Terminal屬性
template<class T> void TERMINAL<T>::resetAttr(void){
	cout << "\x1B[0m";
	mUnderLine = false;
	mCurFColor = ATTR::WHITE;
	mCurBColor = ATTR::BLACK;
}

/* 將所有字元設定成空白字元 */
/* 依參數設定前景、背景 */
/* 預設值前景：白色、背景：黑色、無底線 */
template<class T> void TERMINAL<T>::init(int FColor, int BColor){
	uint8_t blank[] = " ";
	
	setFColor(FColor);
	setBColor(BColor);
	setUnderLine(false);
	
	for (int i=1; i<=mLINS; i++)
		for (int j=1; j<=mCOLS; j++)
			if (setSP(i, j))
			  sp->setChar(blank, mUnderLine, mCurFColor, mCurBColor);
}

// 取得Terminal大小
template<class T> void TERMINAL<T>::getConsoleSize(){
	struct winsize size;
	
	// ioctl()       需要include <sys/ioctl.h>
	// STDOUT_FILENO 需要include <unistd.h>
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
	mLINS = size.ws_row;
	mCOLS = size.ws_col;
}

template<class T> void TERMINAL<T>::createBuffer(void){
	/* 依據Terminal大小建立緩衝區 */
	TermBuf = NEW2D(mLINS, mCOLS, T);
}

/* 設定sp指標值，如果超過螢幕範圍將回傳false */
template<class T> bool TERMINAL<T>::setSP(int pLin, int pCol){
	int lin, col;
	
	if (pLin < 1 || pLin > mLINS)
		return false;
	
	if (pCol < 1 || pCol > mCOLS)
		return false;
	
	lin = pLin - 1;
	col = pCol - 1;
	sp = &TermBuf[lin][col];
	return true;
}

// 以顏色代碼設定前景色，顏色代碼超出範圍無效
template<class T> void TERMINAL<T>::setFColor(int p){
	if (p >= 0 && p <= 255)
	  mCurFColor = p;
}

// 以RGB值設定前景色，RGB值範圍為0~5
template<class T> void TERMINAL<T>::setFColor(int r, int g, int b){
	setFColor(16 + r*36 + g*6 + b);
}

// 以顏色代碼設定背景色，顏色代碼超出範圍無效
template<class T> void TERMINAL<T>::setBColor(int p){
	if (p >= 0 && p <= 255)
	  mCurBColor = p;
}

// 以RGB值設定背景色，RGB值範圍為0~5
template<class T> void TERMINAL<T>::setBColor(int r, int g, int b){
	setBColor(16 + r*36 + g*6 + b);
}

// 設定是否畫底線
template<class T> void TERMINAL<T>::setUnderLine(bool p){
	mUnderLine = p;
}

// 取得終端機列數
template<class T> int TERMINAL<T>::getLINS(){
	return mLINS;
}

// 取得終端機行數
template<class T> int TERMINAL<T>::getCOLS(){
	return mCOLS;
}

template<class T> void TERMINAL<T>::cls(void){
	init(mCurFColor, mCurBColor);
	locate(1, 1);
}

// 設定游標位置
// Lin代表列, Col代表行
// 螢幕左上角為 1, 1
// 設定超過螢幕範圍會自動調整成適合螢幕大小的位置
template<class T> void TERMINAL<T>::locate(int pLin, int pCol){
	char Buf[10];
	
	if (pLin < 1) mCurLin = 1;
	if (pLin > mLINS) mCurLin = mLINS;
	if (pCol < 1) mCurCol = 1;
	if (pCol > mCOLS) mCurCol = mCOLS;
	sprintf(Buf, "\x1B[%d;%dH", mCurLin, mCurCol);
	cout << Buf;
}

template<class T> TERMINAL<T>::~TERMINAL(){
	resetAttr();
	
	for (int i=0; i<mLINS; i++)
		delete[] TermBuf[i];
	
	delete[] TermBuf;
}