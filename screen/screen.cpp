#include <iostream>
#include <string>
#include <stdio.h>
#include <screen.h>

SCREEN::SCREEN(){
	GetConsoleSize(LINS, COLS);
	ScreenBuf = new UTF8SCHAR*[LINS];
	for (int i=0; i<LINS; i++){
		ScreenBuf[i] = new UTF8SCHAR[COLS];
	}
	
  Init();
}

SCREEN::SCREEN(ATTR FColor, ATTR BColor){
	GetConsoleSize(LINS, COLS);
	ScreenBuf = new UTF8SCHAR*[LINS];
	for (int i=0; i<LINS; i++){
		ScreenBuf[i] = new UTF8SCHAR[COLS];
	}
	
  Init(FColor, BColor);	
}

int SCREEN::GetLins(void){
	return LINS;
}

int SCREEN::GetCols(void){
	return COLS;
}

/* 設定游標位置 */
/* Lin代表列, Pos代表行 */
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
	std::cout << Buf;
}

void SCREEN::cls(void){
	std::string str("\x1B[2J");
	std::cout << str;
	Locate(1, 1);
	Init(CurFColor, CurBColor);
}

void SCREEN::SetColor(ATTR FColor, ATTR BColor){
	char Buf[20];
	
	if (BColor == ATTR::Reset){
		BColor = CurBColor;
	}
	
	if (((int)FColor < 30) | ((int)FColor > 37 & (int)FColor < 90) | ((int)FColor > 97)){
		FColor = (ATTR)37;
	}
	
  if ((int)BColor < 40 | (int)BColor > 47){
		BColor = (ATTR)40;
	}	
	
	CurFColor = FColor;
	CurBColor = BColor;
	sprintf(Buf, "\x1B[%d;%dm", (int)FColor, (int)BColor);
	std::cout << Buf;
}

void SCREEN::SetAttr(ATTR attr){
	char buf[10];
	
	sprintf(buf, "\x1B[%dm", (int)attr);
	std::cout << buf;
}

void SCREEN::ResetAttr(void){
	std::cout << "\x1B[0m";
}

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
void SCREEN::Init(ATTR FColor, ATTR BColor){
	int Off;
	uint8_t blank[] = " ";
	
	mActive = false;
	ResetAttr();
	SetColor(FColor, BColor);
	
	for (int i=1; i<=LINS; i++){
		for (int j=1; j<=COLS; j++){
			if (SetSP(i, j)){
			  /* sp = &ScreenBuf[i-1][j-1]; */
			  sp->SetFColor(FColor);
			  sp->SetBColor(BColor);
			  sp->SetChar(blank);
			}
		}
	}	
}

void SCREEN::print(uint8_t *p){
	int len, dlen;
  uint8_t *tmp;
	uint8_t buf[UTF8MAXLEN];
  	
	tmp = p;
	while (*tmp != 0){
		len = Utf8Len(tmp);
		dlen = Utf8DLen(tmp);
		for (int i=0; i<len; i++){
			buf[i] = *tmp;
			tmp++;
		}
		buf[len] = 0;
		tmp++;
	}
}

void SCREEN::show(const bool p){
	mActive = p;
	if (mActive)
		refresh();
}

void SCREEN::refresh(void){
	for (int i=1; i<=LINS; i++)
		for (int j=1; j<=COLS; j++){
			Locate(i, j);
			if (SetSP(i, j)){
			  /* sp = &ScreenBuf[i][j]; */
			  sp->print();
			}
		}
	SetColor(CurFColor, CurBColor);
}

/* 將要顯示的字串儲存在螢幕緩衝區 */
/* 傳回值為實際轉換的長度 */
/* 超過一列會自動換列 */
/* 超過螢幕範圍自動截斷 */
/* 中、日、韓及特殊畫框符號之寬度為2，其餘為1 */
/* 儲存寬度為2的字之後，下一個的緩衝區會被設定成無效字元 */
/* 開始位置若為無效字元，表示前一個字為寬字元，前一個字會被自動設成空白 */
/* 開始位置若位於每列最後一個字元，且要顯示的字為寬字元 */
/* 則該字元及下一列的第一個字元都會被設為? */
int SCREEN::Str2Screen(uint8_t *p){
	int lin, col;
	int tlin, tcol;
	SCHAR *oldsp;
	uint8_t qm[] = "?";
	uint8_t blank[] = " ";
	
	lin = tlin = CurLin;
	col = tcol = CurCol;
	SetSP(lin, col);
	/* sp = &ScreenBuf[lin][col]; */
	if (!sp->IsValid()){  // 如果為無效字元
		if (PrevPos(tlin, tcol)){ // 計算前一個字元的座標
		  oldsp = sp;
			SetSP(tlin, tcol);
			/* tsp = &ScreenBuf[tlin][tcol]; */
			sp->SetChar(blank);
			sp = oldsp;
		}
	}
	
	return 0;
}

/* 將要顯示的字元儲存在螢幕緩衝區 */
/* 超過螢幕範圍自動截斷 */
/* 中、日、韓及特殊畫框符號之寬度為2，其餘為1 */
/* 儲存寬度為2的字之後，下一個的緩衝區會被設定成無效字元 */
/* 開始位置若為無效字元，表示前一個字為寬字元，前一個字會被自動設成空白 */
/* 開始位置若位於每列最後一個字元，且要顯示的字為寬字元 */
/* 則該字元會被設為? */
void SCREEN::Char2Screen(uint8_t *p, int pLin, int pCol){
	SCHAR *oldsp;
	bool IsEndLine = false;       /* 是否為該列最後一個字元 */
	bool IsStartHalfChar = false; /* 起始位置是否位於寬字元的結尾 */
	bool IsEndHalfChar = false;   /* 結束位置是否位於寬字元的開頭 */
	int lin, col;
	int PrevCol, NextCol;
	bool PrevValid, NextValid;
	int len;
	uint8_t qm[] = "?";
	uint8_t blank[] = " ";
	
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
	
	if (col == COLS)
		IsEndLine = true;
	
	oldsp = sp;
	SetSP(lin, col);
	if (!sp->IsValid()){
		IsStartHalfChar = true;
	}
	
  if (!IsEndLine)	{
		SetSP(lin, col+1);
		if (!sp->IsValid()){
			IsEndHalfChar = true;
		}
	}
	
  len = Utf8DLen(p);  /* 判斷字元的顯示寬度 */
	switch (len){
	case 1: /* 代表顯示寬度為1的字元 */
	  SetSP(lin, col);
		sp->SetChar(p);
		if (IsStartHalfChar){
			if (PrevValid){
				SetSP(lin, PrevCol);
				sp->SetChar(blank);
			}
		}
		if (IsEndHalfChar){
			if (NextValid){
				SetSP(lin, NextCol);
				sp-SetChar(blank);
			}
		}
	  break;
	case 2: /* 代表寬字元 */
	  if (SetSP(lin, col)){
			if (!sp->IsValid()){
				if (PrevPos(tlin, tcol)){
					SetSP(tlin, tcol);
					sp->SetChar(blank);
					SetSP(lin, col);
				}
			}
		}
	  break;
	}
	
	sp = oldsp;
	return;
}

/* 處理顯示寬度為1的字元 */
void SCREEN::SingleChar(uint8_t *p, int pLin, int pCol){
	SCHAR *oldsp;
	bool InEndLine = false;    /* 是否為該列最後一個字元 */
	bool StartInHead = false;  /* 列印位置是否位於寬字元的開頭 */
	bool StartInTail = false;  /* 列印位置是否位於寬字元的結尾 */
	int lin, col;
	int PrevCol, NexCol;
	bool PrevValid, NextValid;
	uint8_t blank[] = " ";
	
	lin = pLin;
	col = PrevCol = NextCol = pCol;
	
	oldsp = sp;
	
	if (col == COLS)
		InEndLine = true;
	
	PrevValid = PrevPos(PrevCol);
	NextValid = NextPos(NextCol);
	
	SetSP(lin, col);
	if (!sp->IsValid()){
		StartInHalfChar = true;
	}
	
	SetSP(lin, NextCol);
	
	
	sp = oldsp;
}

/* 處理顯示寬度為1的字元 */
void SCREEN::WideChar(uint8_t *p, int pLin, int pCol){
	
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

bool SCREEN::InHead(){
	int len;
	
	len = sp->DLen();
	if (len == 2)
		return true;
	else
		return false;
}

bool SCREEN::InTail(){
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