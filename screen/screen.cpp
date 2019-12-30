#include <iostream>
#include <stdio.h>
#include <screen.h>

SCREEN::SCREEN(){
	GetConsoleSize(LINS, COLS);         // 取得螢幕大小(總列數及每列字數)
	CreateBuffer();
  Init();
}

SCREEN::SCREEN(int FColor, int BColor){
	GetConsoleSize(LINS, COLS);
	CreateBuffer();
  Init(FColor, BColor);	
}

void SCREEN::CreateBuffer(void){
	/* 依據螢幕大小建立螢幕緩衝區 */
	ScreenBuf = new UTF8SCHAR*[LINS];  // 依據螢幕總列數建立UTF8SCHAR指標陣列
	for (int i=0; i<LINS; i++){
		/* 依據螢幕每列字數建立UTF8SCHAR物件陣列 */
		ScreenBuf[i] = new UTF8SCHAR[COLS];  
	}
}

int SCREEN::GetLins(void){
	return LINS;
}

int SCREEN::GetCols(void){
	return COLS;
}

/* 設定游標位置 */
/* Lin代表列, Col代表行 */
/* 螢幕左上角為 1, 1 */
/* 設定超過螢幕範圍會自動調整成適合螢幕大小的位置 */
void SCREEN::Locate(int Lin, int Col){
	char Buf[10];
	
	if (Lin < 1) Lin = 1;
	if (Lin > LINS) Lin = LINS;
	if (Col < 1) Col = 1;
	if (Col > COLS) Col = COLS;
	CurLin = Lin;
	CurCol = Col;
	sprintf(Buf, "\x1B[%d;%dH", Lin, Col);
	cout << Buf;
}

void SCREEN::cls(void){
	/*std::string str("\x1B[2J");
	std::cout << str;
	Locate(1, 1);*/
	Init(CurFColor, CurBColor);
	refresh();
	Locate(1, 1);
}

void SCREEN::SetUnderLine(bool p){
	UnderLine = p;
}

// 以顏色代碼設定前景色，顏色代碼超出範圍無效
void SCREEN::SetFColor(int p){
	if (p >= 0 && p <= 255)
	  CurFColor = p;
}

// 以RGB值設定前景色，RGB值範圍為0~5
void SCREEN::SetFColor(int r, int g, int b){
	SetFColor(16 + r*36 + g*6 + b);
}

// 以顏色代碼設定背景色，顏色代碼超出範圍無效
void SCREEN::SetBColor(int p){
	if (p >= 0 && p <= 255)
	  CurBColor = p;
}

// 以RGB值設定背景色，RGB值範圍為0~5
void SCREEN::SetBColor(int r, int g, int b){
	SetBColor(16 + r*36 + g*6 + b);
}

// 重設螢幕屬性
void SCREEN::ResetAttr(void){
	cout << "\x1B[0m";
	UnderLine = false;
	CurFColor = ATTR::WHITE;
	CurBColor = ATTR::BLACK;
}

// 取得螢幕大小
void SCREEN::GetConsoleSize(int &LINS, int &COLS){
	struct winsize size;
	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); /* ioctl()       需要include <sys/ioctl.h> */
	                                         /* STDOUT_FILENO 需要include <unistd.h> */
	LINS = size.ws_row;
	COLS = size.ws_col;
}

/* 將所有字元設定成空白字元 */
/* 依參數設定前景、背景 */
/* 預設值前景：白色，背景：黑色 */
void SCREEN::Init(int FColor, int BColor){
	int Off;
	uint8_t blank[] = " ";
	
	mActive = false;
	SetFColor(FColor);
	SetBColor(BColor);
	SetUnderLine(false);
	
	for (int i=1; i<=LINS; i++){
		for (int j=1; j<=COLS; j++){
			if (SetSP(i, j)){
			  sp->SetChar(blank, UnderLine, CurFColor, CurBColor);
			}
		}
	}	
}

// 根據傳送過來的檔名讀取該檔內容並印在螢幕上
// 檔案第一行必須有四個數字也以逗號分隔
// 四個數字代表的意義分別為：列,行,前景色,背景色
bool SCREEN::PrintFromFile(const char *filename){
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
	
	SetFColor(fcolor);
	SetBColor(bcolor);
	while (getline(scr, buf)){
		Locate(lin, col);
		print(buf);
		lin++;
	}
	scr.close();
	return true;
}

void SCREEN::print(const string p){
	print((uint8_t*)p.c_str());
}

void SCREEN::print(const char *p){
	print((uint8_t*)p);
}

void SCREEN::print(uint8_t *p){
	SCHAR *oldsp;
	int lin, col;
	int PrevCol, NextCol;
	int StartCol, EndCol;
	int len, j;
 
  lin = CurLin;
	col = StartCol = PrevCol = CurCol;
	
	oldsp = sp;
  SetSP(lin, col); // 指標指向開頭顯示位置
	if (InWideTail()) // 如果開頭位置為寬字元之後半部
		if (PrevPos(PrevCol)) // 如果前一個字元未超過螢幕範圍
			StartCol = StartCol - 1;  // 將開始重印位置指向前一字元
	
  len = Utf8RealDLen(p);  // 計算實際列印長度
	EndCol = col + len - 1;
	if (EndCol > COLS)
		EndCol = COLS;
	SetSP(lin, EndCol);
	if (InWideHead())  // 要列印的最後一個字元位於位於寬字元開頭
		NextPos(EndCol);  // 將結束重印位置指向字串結尾的後一個字元
	
	len = Str2Screen(p);
	if (mActive){
		for (j=StartCol; j<=EndCol; j++){
			Locate(lin, j);
			SetSP(lin, j);
			sp->print();
		}
		Locate(lin, j);
	}
	
	sp = oldsp;
}

void SCREEN::printcode(int lin, int col){
	if (lin < 1)
		lin = 1;
	if (lin > LINS)
		lin = LINS;
	if (col < 1)
		col = 1;
	if (col > COLS)
		col = COLS;
	cout << ScreenBuf[lin-1][col-1];
}

void SCREEN::SetActive(const bool p){
	if (mActive != p){
	  mActive = p;
		if (mActive)
			refresh();
	}
}

void SCREEN::refresh(void){
	int OldLin, OldCol;
	
	if (!mActive)
		return;
	
	OldLin = CurLin;
	OldCol = CurCol;
	for (int i=1; i<=LINS; i++)
		for (int j=1; j<=COLS; j++){
			Locate(i, j);
			if (SetSP(i, j)){
			  sp->print();
			}
		}
	Locate(OldLin, OldCol);
}

void SCREEN::refresh(int pLin, int pStrCol, int pEndCol){
	int OldLin, OldCol;
	SCHAR *oldsp;
	
	if (pLin < 1 || pLin > LINS)
		return;
	
	if (pStrCol < 1)
		pStrCol = 1;
	
	if (pEndCol > COLS)
		pEndCol = COLS;
	
	OldLin = CurLin;
	OldCol = CurCol;
	oldsp = sp;
	
	SetSP(pLin, pStrCol);
	if (InWideTail())
		if (PrevPos(pStrCol))
			pStrCol = pStrCol - 1;
		
	for (int j=pStrCol; j<=pEndCol; j++){
		Locate(pLin, j);
		if (SetSP(pLin, j))
			sp->print();
	}	
	
	Locate(OldLin, OldCol);
	sp = oldsp;
}

/* 將要顯示的字串儲存在螢幕緩衝區 */
/* 傳回值為實際轉換的長度 */
/* 將字串擷取成單一字元給Char2Screen()處理 */
int SCREEN::Str2Screen(uint8_t *p){
	int lin, col;
	int len, rlen;
	uint8_t buf[100];
	
	lin = CurLin;
	col = CurCol;
	len = Utf8RealLen(p);  // 計算要列印字串的字數，無論中、英文字元都算一個字
	rlen = 0;
	for (int i=1; i<=len; i++){
		Utf8Mid(p, buf, i, 1);
		Char2Screen(buf, lin, col);
		if (Utf8DLen(buf) == 2){
			col = col + 2;
			rlen = rlen + 2;
		} else {
			col = col + 1;
			rlen = rlen + 1;
		}
		
		if (col > COLS)
			break;
	}
	return rlen;
}

/* 將要顯示的字元儲存在螢幕緩衝區 */
/* 超過螢幕範圍自動截斷 */
/* 判斷要顯示的字元是寬字元還是單字元，依據結果分開處理 */
/* 中、日、韓及特殊畫框符號之寬度為2，其餘為1 */
void SCREEN::Char2Screen(uint8_t *p, int pLin, int pCol){
	int len;
	
	if (pLin < 1 || pLin > LINS){
		return;
	}
	
	if (pCol < 1 || pCol > COLS){
		return;
	}
	
	len = Utf8DLen(p);
	switch (len){
		case 1:
		  SingleChar(p, pLin, pCol);
			break;
			
		case 2:
		  WideChar(p, pLin, pCol);
			break;
	}
	
	return;
}

/* 處理顯示寬度為1的字元 */
/* 將要顯示的字元儲存在螢幕緩衝區 */
/* 超過螢幕範圍自動截斷 */
/* 開始位置若為無效字元，表示前一個字為寬字元，前一個字會被自動設成空白 */
/* 開始位置若為寬字元，下一個字會被自動設成空白 */
/* 開始位置若位於每列最後一個字元，且要顯示的字為寬字元 */
/* 則該字元會被設為空白 */
void SCREEN::SingleChar(uint8_t *p, int pLin, int pCol){
	SCHAR *oldsp;
	int lin, col;
	int PrevCol, NextCol;
	bool PrevValid, NextValid;
	uint8_t blank[] = " ";
	
	lin = pLin;
	col = PrevCol = NextCol = pCol;
	
	oldsp = sp;
	
	PrevValid = PrevPos(PrevCol);
	NextValid = NextPos(NextCol);
	
	SetSP(lin, col);
	if (InWideHead()){     // 如果位於寬字元開頭，把下半個字元設定成空白
		if (NextValid){         
			SetSP(lin, NextCol);  
			sp->SetChar(blank, UnderLine, CurFColor, CurBColor);
		}
	} else if (InWideTail()){  // 如果位於寬字元結尾，把前半個字元設定成空白
	  if (PrevValid){
			SetSP(lin, PrevCol);
			sp->SetChar(blank, UnderLine, CurFColor, CurBColor);
		}
	}
	
	SetSP(lin, col);  // 指標指向座標位置
	sp->SetChar(p, UnderLine, CurFColor, CurBColor);   // 存入欲顯示字元
	
	sp = oldsp;
}

/* 處理顯示寬度為2的字元 */
/* 將要顯示的字元儲存在螢幕緩衝區 */
/* 超過螢幕範圍自動截斷 */
/* 儲存寬度為2的字之後，下一個的緩衝區會被設定成無效字元 */
/* 開始位置若為無效字元，表示前一個字為寬字元，前一個字會被自動設成空白 */
/* 開始位置若位於每列最後一個字元，且要顯示的字為寬字元 */
/* 則該字元會被設為空白 */
void SCREEN::WideChar(uint8_t *p, int pLin, int pCol){
	SCHAR *oldsp;
	int lin, col;
	int PrevCol, NextCol, NNextCol;
	bool PrevValid, NextValid, NNextValid;
	uint8_t blank[] = " ";
	
	lin = pLin;
	col = PrevCol = NextCol = pCol;
	oldsp = sp;
	
	PrevValid = PrevPos(PrevCol);
	NextValid = NextPos(NextCol);
	if (NextValid){
		NNextCol = NextCol;
		NNextValid = NextPos(NNextCol);
	} else {
		NNextValid = false;
	}
	
	SetSP(lin, col);
	if (InWideTail()){  // 如果顯示位置位於寬字元結尾
	  if (PrevValid){  // 如果前個字元未超過螢幕範圍，把該字元設定成空白
			SetSP(lin, PrevCol);
			sp->SetChar(blank, UnderLine, CurFColor, CurBColor);
		}
	}
	
	if (NextValid){ // 如果下個字元未超出螢幕範圍
		SetSP(lin, NextCol); // 指標指向下一個字元
		if (InWideHead()){ // 如果下個字元位於寬字元開頭
			if (NNextValid){  // 如果下下個字元未超出螢幕範圍
				SetSP(lin, NNextCol); // 指標指向下下個字元
				sp->SetChar(blank, UnderLine, CurFColor, CurBColor); // 把下下個字元設成空白
			}
		}
	}
	
	SetSP(lin, col);  // 指標指向欲顯示位置
	if (NextValid){   // 如果下個字元未超出螢幕範圍
		sp->SetChar(p, UnderLine, CurFColor, CurBColor);  // 存入欲顯示字元
		SetSP(lin, NextCol);  // 指標指向下個字元
		sp->SetValid(false);  // 將下個字元設定成無效字元
	} else {  // 如果下個字元超出螢幕範圍
		sp->SetChar(blank, UnderLine, CurFColor, CurBColor); // 將欲顯示字元設定成空白
	}
	
	sp = oldsp;
}

/* 設定sp指標值，如果超過螢幕範圍將回傳false */
bool SCREEN::SetSP(int pLin, int pCol){
	int lin, col;
	
	if (pLin < 1 || pLin > LINS)
		return false;
	
	if (pCol < 1 || pCol > COLS)
		return false;
	
	lin = pLin - 1;
	col = pCol - 1;
	sp = &ScreenBuf[lin][col];
	return true;
}


/* 計算傳入游標位置之前一個字元的游標位置 */
/* 傳回值若為false表示已在每列最左邊，參數pLin及pCol之值將不會改變 */
bool SCREEN::PrevPos(int &pCol){
	int tcol;
	
	tcol = pCol - 1;
	if (tcol < 1){
    return false;
	}
	
	pCol = tcol;
	return true;
}

/* 計算傳入游標位置之下一個字元的游標位置 */
/* 傳回值若為false表示已在螢幕最右邊，參數pLin及pCol之值將不會改變 */
bool SCREEN::NextPos(int &pCol){
	int tcol;
	
	tcol = pCol + 1;
	if (tcol > COLS){
 	  return false;
	}
	
	pCol = tcol;
	return true;
}

bool SCREEN::InWideHead(){
	int len;
	
	len = sp->DLen();
	if (len == 2)
		return true;
	else
		return false;
}

bool SCREEN::InWideTail(){
	if (sp->IsValid())
		return false;
	else
		return true;
}

SCREEN::~SCREEN(){
	ResetAttr();
	for (int i=0; i<LINS; i++)
		delete[] ScreenBuf[i];
	
	delete[] ScreenBuf;
}