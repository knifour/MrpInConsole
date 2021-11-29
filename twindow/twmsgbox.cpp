#include <iostream>
#include <stdio.h>
#include <vector>
#include <twmsgbox.h>

template <class T> TWMSGBOX<T>::TWMSGBOX(){
	this->mError = true;
}

template <class T> TWMSGBOX<T>::TWMSGBOX(TWINDOW<T>* p, const char* msg, WIN win){
	if (p == nullptr){
		this->mError = true;
		return;
	}
	
	this->mTerminal = p->getTerminal();
	this->mParant = p;
	p->addChild(this);
	
	int LINS = p->getLINS();
	int COLS = p->getCOLS();
	
	char delim[] = "\n";
	vector<string> buf;
	
	int lins = splitStr(msg, delim, buf) + 2;
	int code;
	
	if (lins > LINS){
		this->mError = true;
		return;
	}
	
	int cols = -1;
	int temp;
	for (auto it=buf.begin(); it!=buf.end(); it++){
		temp = getDisplayLength(*it);
		if (temp > cols)
			cols = temp;
	}
	if (cols%2==1)
		cols++;
	cols = cols + 4;
	
	this->mVisible = false;
	this->mLin = (LINS - lins) / 2 + 1;
	this->mCol = (COLS - cols) / 2 + 1;
	this->mLINS = lins;
	this->mCOLS = cols;
	
	if (win.FColor == 0)
	  win.FColor = this->mTerminal->getFColor();
	
	if (win.BColor == 0)
		win.BColor = this->mTerminal->getBColor();
	
	this->mUnderline = false;
	this->mError = false;
	this->createBuffer();
	this->init(win.FColor, win.BColor);
	
	int tmpLin = 1;
	int tmpCol = 1;
	this->locate(tmpLin, tmpCol);
	this->print(SUL);
	tmpCol = tmpCol + 2;
	for (int i=1; i<=cols; i=i+2){
		this->locate(tmpLin, tmpCol);
		this->print(SHZ);
		tmpCol = tmpCol + 2;
	}
	this->locate(tmpLin, tmpCol);
	this->print(SUR);
	
	tmpLin++;
	for (auto it=buf.begin(); it!=buf.end(); it++){
		tmpCol = 1;
	  this->locate(tmpLin, tmpCol);
	  this->print(SVT);
	  tmpCol = tmpCol + 2;
	  this->locate(tmpLin, tmpCol);
	  this->print(*it);
	  this->locate(tmpLin, cols-1);
	  this->print(SVT);
		tmpLin++;
	}
	
	tmpCol = 1;
	this->locate(tmpLin, tmpCol);
	this->print(SDL);
	tmpCol = tmpCol + 2;
	for (int i=1; i<=cols; i=i+2){
		this->locate(tmpLin, tmpCol);
		this->print(SHZ);
		tmpCol = tmpCol + 2;
	}
	this->locate(tmpLin, tmpCol);
	this->print(SDR);
}

template<class T> void TWMSGBOX<T>::show(void){
	/*WIN win;
	
	win.Lin = win.Col = 1;
	win.Lins = this->getLINS();
	win.Cols = this->getCOLS();
	this->mVisible = true;
	this->TWin2Term(win);
	this->reflash(win);*/
	TWINDOW<T>::show();
	cout << "\x7";
	hideCursor();
	getch();
	this->close();
	this->setVisible(false);
	showCursor();
}

template <class T> TWMSGBOX<T>::~TWMSGBOX(){
}

template class TWMSGBOX<UTF8SCHAR>;