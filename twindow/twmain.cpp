#include <iostream>
#include <stdio.h>
#include <twmain.h>

template <class T> TWMAIN<T>::TWMAIN(TERMINAL<T>* t){
	if (t == nullptr){
		this->mError = true;
		return;
	}
	
	this->mTerminal = t;
	this->mParant = nullptr;
	this->mLin = this->mCol = 1;
	this->mLINS = t->mLINS;
	this->mCOLS = t->mCOLS;
	this->mFColor = t->mFColor;
	this->mBColor = t->mBColor;
	this->mUnderline = t->mUnderline;
	this->createBuffer();
	this->mError = false;
	this->init();
}

template <class T> TWMAIN<T>::~TWMAIN(){
	
}

template class TWINDOW<UTF8SCHAR>;