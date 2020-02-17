#include <twmgr.h>

TWMGR::TWMGR(SCREEN *p){
	mParant = p;
	TWCount = -1;
}

TWMGR::~TWMGR(){
}

bool TWMGR::Register(TWINDOW *p){
	if (TWCount >= 9){  // 已到達視窗最大數量
		return false;
	}
	
	TWCount++;
	buf[TWCount] = p;
	return true;
}