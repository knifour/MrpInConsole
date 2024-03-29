#include <terminal.h>

template<class T>TERMINAL<T>::TERMINAL(){
	getConsoleSize();
	createBuffer();
  init();
	cls();
}

template<class T>TERMINAL<T>::TERMINAL(int FColor, int BColor){
	getConsoleSize();
	createBuffer();
  init(FColor, BColor);
	cls();
}

// 重設Terminal屬性
template<class T> void TERMINAL<T>::resetAttr(void){
	cout << "\x1B[0m";
	mUnderLine = false;
	mFColor = ATTR::WHITE;
	mBColor = ATTR::BLACK;
}

/* 將所有字元設定成空白字元 */
/* 依參數設定前景、背景 */
/* 預設值前景：白色、背景：黑色、無底線 */
template<class T> void TERMINAL<T>::init(int FColor, int BColor){
	//uint8_t blank[] = " ";
	char blank[] = "";
	
	setFColor(FColor);
	setBColor(BColor);
	setUnderline(false);
	
	for (int i=1; i<=mLINS; i++)
		for (int j=1; j<=mCOLS; j++){
			if (setSP(i, j)){
			  sp->setChar(blank, mUnderLine, mFColor, mBColor);
			}
		}
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
	/*TermBuf = NEW2D(mLINS, mCOLS, T);*/
	TermBuf = new T*[mLINS];  
	for (int i=0; i<mLINS; i++){
		// 依據螢幕每列字數建立UTF8SCHAR物件陣列
		TermBuf[i] = new T[mCOLS];  
	}
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
	  mFColor = p;
}

// 以RGB值設定前景色，RGB值範圍為0~5
template<class T> void TERMINAL<T>::setFColor(int r, int g, int b){
	setFColor(16 + r*36 + g*6 + b);
}

// 取得前景色
template<class T> int TERMINAL<T>::getFColor(void) const{
	return mFColor;
}

// 以顏色代碼設定背景色，顏色代碼超出範圍無效
template<class T> void TERMINAL<T>::setBColor(int p){
	if (p >= 0 && p <= 255)
	  mBColor = p;
}

// 以RGB值設定背景色，RGB值範圍為0~5
template<class T> void TERMINAL<T>::setBColor(int r, int g, int b){
	setBColor(16 + r*36 + g*6 + b);
}

// 取得背景色
template<class T> int TERMINAL<T>::getBColor(void) const{
	return mBColor;
}

// 設定是否畫底線
template<class T> void TERMINAL<T>::setUnderline(bool p){
	mUnderLine = p;
}

// 取得是否畫底線設定
template<class T> bool TERMINAL<T>::getUnderline(void) const{
	return mUnderLine;
}

// 將特定游標位置的字元設定成傳入的SCHAR字元(超出TERMINAL範圍無效)
template<class T> void TERMINAL<T>::setSchar(int pLin, int pCol, SCHAR* pSchar){
	if (pLin < 1 || pLin > mLINS)
		return;
	
	if (pCol < 1 || pCol > mCOLS)
		return;
	
	if (setSP(pLin, pCol))
		*sp = *pSchar;
}

// 取得終端機列數
template<class T> int TERMINAL<T>::getLINS() const{
	return mLINS;
}

// 取得終端機行數
template<class T> int TERMINAL<T>::getCOLS() const{
	return mCOLS;
}

template<class T> void TERMINAL<T>::cls(void){
	/*init(mFColor, mBColor);*/
	cout << "\x1B[J";
	WIN win;
	reflash(win);
	locate(1, 1);
}

// 設定游標位置
// Lin代表列, Col代表行
// 螢幕左上角為 1, 1
// 設定超過螢幕範圍會自動調整成適合螢幕大小的位置
template<class T> void TERMINAL<T>::locate(int pLin, int pCol){
	char buf[30];
	/*char buf2[30];
	char *ap=buf2;
	char *gotostr;*/
	
	if (pLin < 1 || pLin > mLINS)
		return;
	else
		mCurLin = pLin;
	
	if (pCol < 1 || pCol > mCOLS)
		return;
	else
		mCurCol = pCol;
	sprintf(buf, "\x1B[%d;%dH", mCurLin, mCurCol);
	cout << buf;
	/*tgetent(buf, getenv("TERM"));
	gotostr = tgetstr("cm", &ap);
	fputs(tgoto(gotostr, mCurCol-1, mCurLin-1), stdout);*/
}

template<class T> void TERMINAL<T>::reflash(WIN win){
  int tmpLin, tmpCol;
	
	// 如果沒有傳入參數或是所有參數皆為0表示更新全終端機
	if (win.Lin == 0 && win.Col == 0 && win.Lins == 0 && win.Cols == 0){
		win.Lin = win.Col = 1;
		win.Lins = mLINS;
		win.Cols = mCOLS;
	} else {
		// 傳入參數錯誤時不處理返回
	  if (win.Lin < 1 || win.Lin > mLINS) return;
	  if (win.Col < 1 || win.Col > mCOLS) return;
    //if (win.Lins < 1 || win.Lins > (mLINS-win.Lin+1)) return;
		//if (win.Cols < 1 || win.Cols > (mCOLS-win.Col+1)) return;
	}
	
	// 計算右下角座標，如果超過終端機範圍，自動調整到終端機範圍
	tmpLin = win.Lin + win.Lins - 1;
	if (tmpLin > mLINS) tmpLin = mLINS;
	tmpCol = win.Col + win.Cols - 1;
	if (tmpCol > mCOLS) tmpCol = mCOLS;
	
	for (int i=win.Lin; i<=tmpLin; i++)
		for (int j=win.Col; j<=tmpCol; j++){
			if (setSP(i, j))
			  if (sp->isValid()){
				  locate(i, j);
				  sp->printChar();
			  } else {
					// 如果要列印的第一個字是無效字元，表示它是寬字元的尾部，所以要從前一個字元開始印
					if (j==win.Col) 
						if (setSP(i, j-1)){
							locate(i, j-1);
							sp->printChar();
						}
				}
		}
}

template<class T> TERMINAL<T>::~TERMINAL(){
	resetAttr();
	
	for (int i=0; i<mLINS; i++)
		delete[] TermBuf[i];
	
	delete[] TermBuf;
}

template class TERMINAL<UTF8SCHAR>;