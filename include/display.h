#ifndef __DISPLAY_H
#define __DISPLAY_H

#include <sys/ioctl.h>  // 使用ioctl函式需使用此標頭檔
#include <unistd.h>     // 有定義STDOUT_FILENO, 使用ioctl時會用到
#include <string.h>
#include <attr.h>
#include <utf8schar.h>
#include <fstream>

using namespace std;

class DISPLAY {
private:
  //成員變數
  bool mShow;
	UTF8SCHAR  **TermBuf;
	SCHAR *sp;
	int mLINS, mCOLS;
	int mCurLin, mCurCol;
	bool mUnderLine;
	
	// 成員函數
	void getConsoleSize(int&, int&);                               // 取得Terminal列數及每列字數
  void createBuffer(void);                                       // 建立顯示緩衝區	
	void init(int FColor=ATTR::WHITE, int BColor=ATTR::BLACK);     // 若未指定參數時預設為黑底、白字
	void resetAttr(void);                                          // 重設所有屬性(包括顏色)
	bool setSP(int, int);                                          // 依照游標位置取得顯示緩衝區指標sp，左上角位置為1,1

protected:

public:

}

#endif