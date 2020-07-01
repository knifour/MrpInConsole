#include <display.h>

DISPLAY::DISPLAY{
	getConsoleSize(mLINS, mCOLS); // 取得Terminal大小(總列數及每列字數)
	createBuffer();
  init();
}

/* 將所有字元設定成空白字元 */
/* 依參數設定前景、背景 */
/* 預設值前景：白色，背景：黑色 */
void DISPLAY::init(int FColor, int BColor){
	int Off;
	uint8_t blank[] = " ";
	
	mShow = false;
	setFColor(FColor);
	setBColor(BColor);
	setUnderLine(false);
	
	for (int i=1; i<=mLINS; i++){
		for (int j=1; j<=mCOLS; j++){
			if (setSP(i, j)){
			  sp->setChar(blank, UnderLine, CurFColor, CurBColor);
			}
		}
	}	
}

// 重設Terminal屬性
void DISPLAY::resetAttr(void){
	cout << "\x1B[0m";
	UnderLine = false;
	CurFColor = ATTR::WHITE;
	CurBColor = ATTR::BLACK;
}

// 取得Terminal大小
void DISPLAY::getConsoleSize(int &LIN, int &COL){
	struct winsize size;
	
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &size); /* ioctl()       需要include <sys/ioctl.h> */
	                                         /* STDOUT_FILENO 需要include <unistd.h> */
	LIN = size.ws_row;
	COL = size.ws_col;
}

void DISPLAY::createBuffer(void){
	/* 依據Terminal大小建立緩衝區 */
	TermBuf = NEW2D(mLINS, mCOLS, UTF8SCHAR);
}

/* 設定sp指標值，如果超過螢幕範圍將回傳false */
bool DISPLAY::setSP(int pLin, int pCol){
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

DISPLAY::~DISPLAY(){
	resetAttr();
	
	delete[] TermBuf;
}