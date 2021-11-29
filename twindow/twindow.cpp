#include <iostream>
#include <stdio.h>
#include <twindow.h>

char SHZ[] = "\xe2\x94\x80\x0";
char SVT[] = "\xe2\x94\x82\x0";
char SUL[] = "\xe2\x94\x8c\x0";
char SUM[] = "\xe2\x94\xac\x0";
char SUR[] = "\xe2\x94\x90\x0";
char SML[] = "\xe2\x94\x9c\x0";
char SMM[] = "\xe2\x94\xbc\x0";
char SMR[] = "\xe2\x94\xa4\x0";
char SDL[] = "\xe2\x94\x94\x0";
char SDM[] = "\xe2\x94\xb4\x0";
char SDR[] = "\xe2\x94\x98\x0";

char DHZ[] = "\xe2\x95\x90\x0";
char DVT[] = "\xe2\x95\x91\x0";
char DUL[] = "\xe2\x95\x94\x0";
char DUM[] = "\xe2\x95\xa6\x0";
char DUR[] = "\xe2\x95\x97\x0";
char DML[] = "\xe2\x95\xa0\x0";
char DMM[] = "\xe2\x95\xac\x0";
char DMR[] = "\xe2\x95\xa3\x0";
char DDL[] = "\xe2\x95\x9a\x0";
char DDM[] = "\xe2\x95\xa9\x0";
char DDR[] = "\xe2\x95\x9d\x0";

// 編譯時可以透過-D定義DOUBLELINE使所有的表格代號定義成雙線
// 如果沒有特別定義時，所有的表格代號都是單線
// 定義方法如下：g++ -DDOUBLELINE
#ifdef DOUBLELINE
char HZ[] = "\xe2\x95\x90\x0";
char VT[] = "\xe2\x95\x91\x0";
char UL[] = "\xe2\x95\x94\x0";
char UM[] = "\xe2\x95\xa6\x0";
char UR[] = "\xe2\x95\x97\x0";
char ML[] = "\xe2\x95\xa0\x0";
char MM[] = "\xe2\x95\xac\x0";
char MR[] = "\xe2\x95\xa3\x0";
char DL[] = "\xe2\x95\x9a\x0";
char DM[] = "\xe2\x95\xa9\x0";
char DR[] = "\xe2\x95\x9d\x0";
#else
char HZ[] = "\xe2\x94\x80\x0";
char VT[] = "\xe2\x94\x82\x0";
char UL[] = "\xe2\x94\x8c\x0";
char UM[] = "\xe2\x94\xac\x0";
char UR[] = "\xe2\x94\x90\x0";
char ML[] = "\xe2\x94\x9c\x0";
char MM[] = "\xe2\x94\xbc\x0";
char MR[] = "\xe2\x94\xa4\x0";
char DL[] = "\xe2\x94\x94\x0";
char DM[] = "\xe2\x94\xb4\x0";
char DR[] = "\xe2\x94\x98\x0";
#endif

template<class T> TWINDOW<T>::TWINDOW(){
	mTerminal = nullptr;
	mParant = nullptr;
	mVisible = false;
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
	WIN win;
	
	if (mError)
		return;
	
	if (mTerminal==nullptr)
		return;
	
	if (sWin.Lin == 0 && sWin.Col == 0 && sWin.Lins == 0 && sWin.Cols == 0){
		sWin.Lin = sWin.Col = 1;
		sWin.Lins = mLINS;
		sWin.Cols = mCOLS;
	}
	
	// 來源列座標超出視窗位置無效
	if (sWin.Lin < 1 || sWin.Lin > mLINS)
		return;
	
	// 來源行座標超出視窗位置無效
	if (sWin.Col < 1 || sWin.Col > mCOLS)
		return;
	
	int LINS = mTerminal->getLINS();
	int COLS = mTerminal->getCOLS();
	
	// 將視窗座標對應到TERMINAL座標
	// win.Lin = mLin + sWin.Lin - 1;
	win.Lin = getRealLin(mParant) + sWin.Lin - 1;
	if (win.Lin < 1 || win.Lin > LINS)
		return;
	// win.Col = mCol + sWin.Col - 1;
	win.Col = getRealCol(mParant) + sWin.Col - 1;
  if (win.Col < 1 || win.Col > COLS)
		return;
	
	// 計算來源視窗右下角座標
	int sBottom = sWin.Lin + sWin.Lins - 1;
	if (sBottom > mLINS)
		sBottom = mLINS;
	int sRight = sWin.Col + sWin.Cols - 1;
	if (sRight > mCOLS)
		sRight = mCOLS;
	
	int tmpLin = win.Lin - 1;
	int tmpCol;
	for (int i=sWin.Lin; i<=sBottom; i++){
		tmpLin++;
		if (tmpLin > LINS)
			break;
		tmpCol = win.Col - 1;
		for (int j=sWin.Col; j<=sRight; j++){
		 tmpCol++;
		 if (tmpCol > COLS)
			 break;
		 if (setSP(i, j))
		   mTerminal->setSchar(tmpLin, tmpCol, sp);
		}
	}
	
	//win.Lins = sWin.Lins;
	//win.Cols = sWin.Cols;
	
	//mTerminal->reflash(win);
}

template<class T> void TWINDOW<T>::init(int FColor, int BColor){
	//uint8_t blank[] = " ";
	char blank[] = " ";
	
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
	
	//WIN win;
	
	//win.Lin = win.Col = 1;
	//win.Lins = mLINS;
	//win.Cols = mCOLS;
	//TWin2Term(win);
	//reflash(win);
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

template<class T> TERMINAL<T>* TWINDOW<T>::getTerminal(void){
	return mTerminal;
}

template<class T> TWINDOW<T>* TWINDOW<T>::getParant(void){
	return mParant;
}

template<class T> vector<TWINDOW<T>*>& TWINDOW<T>::getChildWindow(void){
	return mChild;
}

template<class T> bool TWINDOW<T>::getVisible(void) const {
	return mVisible;
}

template<class T> void TWINDOW<T>::setVisible(bool p){
	mVisible = p;
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

template<class T> int TWINDOW<T>::getLin() const{
	return mLin;
}

template<class T> int TWINDOW<T>::getCol() const{
	return mCol;
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
	int tLin = getRealLin(mParant) + pLin - 1;
	if (tLin > mTerminal->getLINS())
		return;
	int tCol = getRealCol(mParant) + pCol - 1;
	if (tCol > mTerminal->getCOLS())
		return;
	mCurLin = pLin;
	mCurCol = pCol;
	sprintf(buf, "\x1B[%d;%dH", mCurLin, mCurCol);
	cout << buf;
	/*tgetent(buf, getenv("TERM"));
	gotostr = tgetstr("cm", &ap);
	fputs(tgoto(gotostr, mCurCol-1, mCurLin-1), stdout);*/
}

template<class T> int TWINDOW<T>::getRealLin(TWINDOW<T>* p) const{
	if (p==nullptr)
		return mLin;
	else
		return p->mLin+getRealLin(p->mParant)-1;
}

template<class T> int TWINDOW<T>::getRealCol(TWINDOW<T>* p) const{
	if (p==nullptr)
		return mCol;
	else
		return p->mCol+getRealCol(p->mParant)-1;
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
	//uint8_t blank[]=" ";
	char blank[] = " ";
	
	if (mError)
		return;
	
	// 計算要列印的字數(中、英文皆算1字)，若字串含有不合法UTF8字元，則不列印結束
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
	int strCol = mCurCol;
	int tmpCol = mCurCol - 1; // tmpCol儲存列印後游標位置(最後一個字元所在位置)
	//uint8_t tmp[UTF8MAXLEN];
	char tmp[UTF8MAXLEN];
	
  if (setSP(mCurLin, mCurCol)){
		if (sp->isWideTail()){
			strCol--;  // 起始列印游標位置減1
			strPos--;  // 緩衝起始陣列位置減1
		}
	}
	
	for (int i=1; i<=cnt; i++){
		getMidStr(p, (uint8_t*)tmp, i, 1);  // 一次取出一個要顯示的字元放在tmp(寬字元、單字元皆算一個字元)
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
	int realLen = tmpCol - strCol + 1;
	tmpCol = strCol;
	for (int i=strPos; i<=endPos; i++){
		tmpSP = &buf[i];
		setSchar(mCurLin, tmpCol, tmpSP);
		tmpCol++;
	}
	
	WIN win;
	
	win.Lin = mCurLin;
	win.Lins = 1;
	win.Col = strCol;
	win.Cols = realLen;
	
	if (mVisible){
	  if (realLen > 0){
	    TWin2Term(win);
		  reflash(win);
	  }
	}
	
	delete[] buf;
}

template<class T> void TWINDOW<T>::show(void){
	WIN win;
	
	win.Lin = win.Col = 1;
	win.Lins = mLINS;
	win.Cols = mCOLS;
	mVisible = true;
	TWin2Term(win);
	reflash(win);
}

template<class T> void TWINDOW<T>::close(void){
	WIN win;

  if (mParant == nullptr)
    return;
	
	removeChild(this);

  win.Lin = mParant->getLin();
  win.Col = mParant->getCol();
  win.Lins = mParant->getLINS();
  win.Cols = mParant->getCOLS();
	mParant->TWin2Term(win);
  rePaint(mParant->getChildWindow());
  mParant->getTerminal()->reflash(win);	
}

template<class T> void TWINDOW<T>::reflash(WIN win){
	win.Lin = win.Lin + getRealLin(mParant) - 1;
	win.Col = win.Col + getRealCol(mParant) - 1;
	mTerminal->reflash(win);
}

template<class T> void TWINDOW<T>::addChild(TWINDOW<T>* p){
	mChild.push_back(p);
}

template<class T> void TWINDOW<T>::removeChild(TWINDOW<T>* p){
	for (auto it=mChild.begin(); it!=mChild.end(); it++){
		if (*it == p){
			mChild.erase(it);
			break;
		}
	}
}

template<class T> void TWINDOW<T>::rePaint(vector<TWINDOW*>& pChild){
	WIN win;
	
	if (pChild.size() == 0)
		return;
	
	for (auto it=pChild.begin(); it!=pChild.end(); it++){
		win.Lin = (*it)->getLin();
		win.Col = (*it)->getCol();
		win.Lins = (*it)->getLINS();
		win.Cols = (*it)->getCOLS();
		(*it)->TWin2Term(win);
		rePaint(this->getChildWindow());
	}
}

template<class T> bool TWINDOW<T>::printFromFile(const char* filename){
	fstream scr;
	string buf, tmp;
	int cnt;
	int lin, col;
	int fcolor, bcolor;
	
	scr.open(filename, ios::in);
	if (!scr)  // 如果開檔失敗則結束並回傳錯誤
		return false;
	
	if (getline(scr, buf)){ // 讀取第一行
	  cnt = 0;
		for (int i=0; i<buf.length(); i++){
			if (buf.substr(i, 1) == ",")
				cnt++;
		}
		if (cnt != 3){ // 逗點數不是三個，表示參數數量錯誤
			scr.close();  
			return false;  // 結束
		}
		
		cnt = 0;
		tmp = "";
		for (int i=0; i<buf.length(); i++){
			if (buf.substr(i, 1) == ","){
				switch (cnt){
					case 0:
					  lin = stoi(tmp, nullptr);
						tmp = "";
						break;
					case 1:
					  col = stoi(tmp, nullptr);
						tmp = "";
						break;
					case 2:
					  fcolor = stoi(tmp, nullptr);
						tmp = "";
						break;
				}
				cnt++;
				continue;
			}
			tmp = tmp + buf.substr(i, 1);
		}
		bcolor = stoi(tmp, nullptr);
	}
	
	setFColor(fcolor);
	setBColor(bcolor);
	while (getline(scr, buf)){
		locate(lin, col);
		print(buf);
		lin++;
	}
	scr.close();
	return true;
}

template<class T> TWINDOW<T>::~TWINDOW(){
	for (int i=0; i<mLINS; i++)
		delete[] TWindowBuf[i];
	
	delete[] TWindowBuf;
}

template class TWINDOW<UTF8SCHAR>;