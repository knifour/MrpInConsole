#include <twinmsg.h>

TWinMsg::TWinMsg(SCREEN *p, const char *msg, const char *fmt, ...){
	if (p == NULL){
		return;
	} else {
		mParant = p;
	}
	
	va_list ap;
	int LINS, COLS;
	int temp;
	
	LINS = p->GetLins();
	COLS = p->GetCols();
	
	
	/* 開始解析不定數量參數 */
	va_start(ap, fmt);
	while (*fmt){
		switch (*fmt++){
		case 'l':  // 小寫L表示此參數為左上角列座標
		  temp = va_arg(ap, int); // 使用va_arg把參數以int方式轉換出來
			if (temp < 1)
				temp = 1;
			if (temp > LINS)
				temp = LINS;
			mLin = temp;
			break;
		case 'c':  // 小寫C表示此參數為左上角行座標
		  temp = va_arg(ap, int); // 使用va_arg把參數以int方式轉換出來
			if (temp < 1)
				temp = 1;
			if (temp > COLS)
				temp = COLS;
			mCol = temp;
			break;
		case 'L':  // 大寫L表示此參數為視窗總列數
		  temp = va_arg(ap, int); // 使用va_arg把參數以int方式轉換出來
			if (temp < 1)
				temp = 1;
			if (temp > LINS)
				temp = LINS;
			mLINS = temp;
			break;
		case 'C':  // 大寫C表示此參數為視窗總行數
		  temp = va_arg(ap, int); // 使用va_arg把參數以int方式轉換出來
			if (temp < 1)
				temp = 1;
			if (temp > COLS)
				temp = COLS;
			mCOLS = temp;
			break;
		case 'F':  // 大寫F表示此參數為視窗前景色
		  temp = va_arg(ap, int); // 使用va_arg把參數以int方式轉換出來
			if (temp < 0 || temp > 255)
				temp = 7;
			mFColor = temp;
			break;
		case 'B':  // 大寫B表示此參數為視窗前景色
		  temp = va_arg(ap, int); // 使用va_arg把參數以int方式轉換出來
			if (temp < 0 || temp > 255)
				temp = 0;
			mBColor = temp;
			break;
		}
	}
	va_end(ap);
	/* 不定數量參數解析完成 */
	
}

TWinMsg::~TWinMsg(){
	
}