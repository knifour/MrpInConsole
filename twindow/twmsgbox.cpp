#include <iostream>
#include <stdio.h>
#include <twmsgbox.h>

template <class T> TWMSGBOX<T>::TWMSGBOX(){
	this->mError = true;
}

template <class T> TWMSGBOX<T>::TWMSGBOX(TWINDOW<T>* p, const char* msg){
	if (p == nullptr){
		this->mError = true;
		return;
	}
	
	this->mTerminal = p->mTerminal;
	this->mParant = p;
	
	int len = getDisplayLength(msg);
	if (len < 1){
		mError = true;
		return;
	}
	
	int LINS = p->getLINS();
	int COLS = p->getCOLS();
	
	this->mLin = this->mCol = 1;
	this->mLINS = t->getLINS();
	this->mCOLS = t->getCOLS();
	this->mFColor = t->getFColor();
	this->mBColor = t->getBColor();
	this->mUnderline = t->getUnderline();
	this->mError = false;
	this->createBuffer();
	this->init();
}

template <class T> TWMSGBOX<T>::~TWMSGBOX(){
	
}

template class TWMSGBOX<UTF8SCHAR>;