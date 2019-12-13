#ifndef __SCREEN_H
#define __SCREEN_H

#include <sys/ioctl.h>
#include <unistd.h>
#include <attr.h>
#include <utf8schar.h>

class SCREEN {
public:	
	SCREEN();
	SCREEN(ATTR FColor, ATTR BColor=ATTR::BBlack);
	~SCREEN();
	int GetLins(void);
	int GetCols(void);
	void Locate(int, int);
	void SetColor(ATTR FColor, ATTR BColor=ATTR::Reset);
	void SetAttr(ATTR);
	void ResetAttr(void);
	void cls(void);
	void GetConsoleSize(int &, int &);
	void print(uint8_t *p);
	void SetActive(bool const);
	void refresh(void);

private:
  bool mActive;                                                  /* 是否顯示 */
  UTF8SCHAR **ScreenBuf;                                         /* 螢幕緩衝區 */
  SCHAR *sp;                                                     /* 螢幕操作指標 */
	int LINS, COLS;                                                /* LINS,COLS : 總列數,總行數, 由建構式取得其值 */
	int CurLin, CurCol;                                            /* CurLin,CurCol 游標所在列、行 */
	ATTR CurFColor, CurBColor;                                     /* CurFColor, CusBColor 現在的前景、背景色 */
	void Init(ATTR FColor=ATTR::FWhite, ATTR BColor=ATTR::BBlack); /* 螢幕物件初始化，可於初始化時設定顏色 */
	int Str2Screen(uint8_t *p);                                    /* 將要列印的字串轉存到螢幕緩衝區 */
  void Char2Screen(uint8_t *p, int pLin, int pCol);              /* 將要列印的字元存進螢幕緩衝區 */
  void SingleChar(uint8_t *p, int pLin, int pCol);               /* 處理寬度為1的字元 */
  void WideChar(uint8_t *p, int pLin, int pCol);	               /* 處理寬度為2的字元 */
  bool SetSP(int pLin, int pCol);                                /* 依照游標位置取得螢幕緩衝區指標sp，螢幕左上角位置為1,1 */	
	bool PrevPos(int&);                                            /* 計算上一個游標位置 */
	bool NextPos(int&);                                            /* 計算下一個游標位置 */
  bool InHead();                                                 /* 根據sp值判斷是否位於寬字元開頭，呼叫前先設定sp指標值 */
  bool InTail();	                                               /* 根據sp值判斷是否位於寬字元結尾，呼叫前先設定sp指標值 */
};

#endif