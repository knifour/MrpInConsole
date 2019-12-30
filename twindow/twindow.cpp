#include <iostream>
#include <stdio.h>
#include <twindow.h>

TWINDOW::TWINDOW(TWS p){
	if (p.parant == NULL){  // 若沒有設定父視窗指標
		mError = true;
		return;
	}
	
}