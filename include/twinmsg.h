/* 類別名稱TWinMsg表示為TERMINAL WINDOW MESSAGE之意 */

#ifndef __TWINMSG_H
#define __TWINMSG_H

#include <string>
#include <stdarg.h>
#include <screen.h>
#include <twindow.h>
#include <stdint.h>
#include <util.h>

using namespace std;

class TWinMsg : public TWINDOW{
public:
  /* 建構函式第一個參數為父視窗指標 */
	/* 第二個參數為常數字串 */
	TWinMsg(SCREEN*, const uint8_t *); /* 在SCREEN正中間顯示訊息，按任意鍵關閉視窗 */
  TWinMsg(SCREEN*, const uint8_t *, const char *, ...);
	~TWinMsg();

protected:
};

#endif