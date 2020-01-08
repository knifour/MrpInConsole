#ifndef __SCREEN_H
#define __SCREEN_H

#include <sys/ioctl.h>
#include <unistd.h>
#include <string>
#include <attr.h>
#include <utf8schar.h>
#include <fstream>

using namespace std;

class SCREEN {
public:	
	SCREEN();                                                      // 無參數建構式，預設為黑底、白字
	SCREEN(int FColor, int BColor=ATTR::BLACK);                    // 有參數建構式，傳一個參數指定前景色、背景色為黑色，傳兩個參數指定前景色、背景色
	~SCREEN();                                                     // 解構式，釋放螢幕緩衝區記憶體，恢復黑底、白字
	int GetLins(void);                                             // 取得螢幕列數
	int GetCols(void);                                             // 取得螢幕每列字數
	void Locate(int, int);                                         // 設定游標位置
	void SetFColor(int);
	void SetFColor(int, int, int);
	void SetBColor(int);
	void SetBColor(int, int, int);
	void SetUnderLine(bool);
	void ResetAttr(void);                                          // 重設所有屬性(包括顏色)
	void cls(void);                                                // 清除螢幕
	bool PrintFromFile(const char *filename);                      // 讀取檔案並把它印在螢幕上面，第一行有四個參數，分別指定->列,行,前景色,背景色
	void print(const char *p);                                     // 將字串印在螢幕上面，可接受三種參數 char*、string、uint8_t*
	void print(const string p);
	void print(uint8_t *p);
	void printcode(int, int);
	void SetActive(bool const);                                    // 設定螢幕是否為顯示狀態
	void Refresh(void);                                            // 根據螢幕緩衝區的內容刷新螢幕
  void Refresh(int, int, int);                                   // 第一個參數指定重印某一列，第二、三個參數指定重印的起始、終止字元	

private:
  // 成員變數
  bool mActive;                                                  // 是否顯示
  UTF8SCHAR **ScreenBuf;                                         // 螢幕緩衝區
  SCHAR *sp;                                                     // 螢幕操作指標
	int LINS, COLS;                                                // LINS,COLS : 總列數,總行數, 由建構式取得其值
	int CurLin, CurCol;                                            // CurLin,CurCol 游標所在列、行
  int CurFColor, CurBColor;                                      // 儲存現有前景色、背景色	
	bool UnderLine;                                                // 是否畫底線
	
	// 成員函數
	void GetConsoleSize(int &, int &);                             // 取得螢幕列數及每列字數
  void CreateBuffer(void);                                       // 建立螢幕緩衝區	
	void Init(int FColor=ATTR::WHITE, int BColor=ATTR::BLACK);     // 若未指定參數時預設為黑底、白字                 // 螢幕物件初始化，可於初始化時設定顏色
	int Str2Screen(uint8_t *p);                                    // 將要列印的字串轉存到螢幕緩衝區
  void Char2Screen(uint8_t *p, int pLin, int pCol);              // 將要列印的字元存進螢幕緩衝區
  void SingleChar(uint8_t *p, int pLin, int pCol);               // 處理寬度為1的字元
  void WideChar(uint8_t *p, int pLin, int pCol);	               // 處理寬度為2的字元
  bool SetSP(int pLin, int pCol);                                // 依照游標位置取得螢幕緩衝區指標sp，螢幕左上角位置為1,1
	bool PrevPos(int&);                                            // 計算上一個游標位置
	bool NextPos(int&);                                            // 計算下一個游標位置
  bool InWideHead();                                             // 根據sp值判斷是否位於寬字元開頭，呼叫前先設定sp指標值
  bool InWideTail();	                                           // 根據sp值判斷是否位於寬字元結尾，呼叫前先設定sp指標值
};

#endif