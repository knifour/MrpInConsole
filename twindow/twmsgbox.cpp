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
	  this->mFColor = this->getFColor();
	else
		this->mFColor = win.FColor;
	
	if (win.BColor == 0)
		this->mBColor = this->getBColor();
	else
		this->mBColor = win.BColor;
	
	this->mUnderline = false;
	this->mError = false;
	this->createBuffer();
	this->init();
	
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
	tmpCol = 1;
	this->locate(tmpLin, tmpCol);
	this->print(SVT);
	tmpCol = tmpCol + 2;
	this->locate(tmpLin, tmpCol);
	this->print(msg);
	this->locate(tmpLin, cols-1);
	this->print(SVT);
	
	tmpLin++;
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

template <class T> TWMSGBOX<T>::~TWMSGBOX(){
	
}

template class TWMSGBOX<UTF8SCHAR>;