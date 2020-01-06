/* 類別名稱TMsg表示為TERMINAL WINDOW MESSAGE之意 */

#ifndef __TWINMSG_H
#define __TWINMSG_H

#include <string>
#include <screen.h>
#include <twindow.h>

using namespace std;

class TWinMsg : public TWINDOW{
public:
  /* 建構函式第一個參數為父視窗指標 */
	/* 第二個參數為常數字串 */
  TWinMsg(SCREEN*, const char *, const char *, ...);
	~TWinMsg();

protected:
};

#endif