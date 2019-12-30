#include <iostream>
#include <stdio.h>
#include <twindow.h>

TWINDOW::TWINDOW(TWS p){
	int ln, cl;
	
	tws = p;
	
	if (tws.parant == NULL){  // 若沒有設定父視窗指標
		mError = true;  // 將視窗設定為不能使用狀態
		return;
	}
	
	ln = tws.parant->GetLins();
	cl = tws.parant->GetCols();
	if (tws.lin < 1 || tws.lin > ln){  // 如果視窗左上角列座標超過螢幕範圍
		mError = true;
		return;
	}
	
	if (tws.col < 1 || tws.col > cl){  // 如果視窗左上角行座標超過螢幕範圍
		mError = true;
		return;
	}
	
	if ((tws.lin+tws.LINS-1) > ln){  // 如果視窗右下角列座標超過螢幕範圍
		mError = true;
		return;
	}
	
	if ((tws.col+tws.COLS-1) > cl){  // 如果視窗右下角行座標超過螢幕範圍
		mError = true;
		return;
	}
	
	if ((tws.Board && tws.LINS < 3) || (tws.Board && tws.COLS < 6)){  // 如果有設定外框且列數少於3或行數少於6
		mError = true;
		return;
	}
	
	if (tws.FColor < 0 || tws.FColor > 255) // 如果前景色超出範圍
		tws.FColor = 7;
	
	if (tws.BColor < 0 || tws.BColor > 255) // 如果背景色超出範圍
		tws.BColor = 0;
		
	mError = false;
	mVisible = false;
	
	TWinBuf = new UTF8SCHAR*[tws.LINS];  // 依據視窗總列數建立UTF8SCHAR指標陣列
	for (int i=0; i<tws.LINS; i++){
		/* 依據視窗每列字數建立UTF8SCHAR物件陣列 */
		TWinBuf[i] = new UTF8SCHAR[tws.COLS];  
	}
}

TWINDOW::~TWINDOW(){
	for (int i=0; i<tws.LINS; i++)
		delete[] TWinBuf[i];
	
	delete[] TWinBuf;
}