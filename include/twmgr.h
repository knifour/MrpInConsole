/* 類別名稱TWMGR表示為TERMINAL WINDOW MANAGER之意 */
/* 此類別管理所有的視窗類別(判斷視窗是否重疊及何時須重繪) */

#ifndef __TWMGR_H
#define __TWMGR_H

#include <screen.h>
#include <twindow.h>
#include <stdint.h>

class TWMGR{
public:
  TWMGR(SCREEN *p);
	~TWMGR();
	bool Register(TWINDOW *p);

private:
  SCREEN *mParant;
	uint8_t **ScreenOverlay;
	TWINDOW *buf[10];
	uint8_t **Overlay[10];
	int TWCount;
};

#endif