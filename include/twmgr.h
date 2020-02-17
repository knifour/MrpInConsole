/* 類別名稱TWMGR表示為TERMINAL WINDOW MANAGER之意 */
/* 此類別管理所有的視窗類別(判斷視窗是否重疊及何時須重繪) */

#ifndef __TWMGR_H
#define __TWMGR_H

#include <screen.h>
#include <twindow.h>

class TWMGR{
public:
  TWMGR(SCREEN *p);
	~TWMGR();
	bool Register(TWINDOW *p);

private:
  SCREEN *mParant;
	TWINDOW *buf[10];
	int TWCount;
};

#endif