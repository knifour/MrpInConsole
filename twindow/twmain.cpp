#include <iostream>
#include <stdio.h>
#include <twmain.h>

template <class T> TWMAIN<T>::TWMAIN(){
	this->mError = true;
}

template <class T> TWMAIN<T>::TWMAIN(TERMINAL<T>* t){
	if (t == nullptr){
		this->mError = true;
		return;
	}
	
	this->mTerminal = t;
	this->mParant = nullptr;
	this->mVisible = false;
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

template <class T> TWMAIN<T>::~TWMAIN(){
	
}

template class TWMAIN<UTF8SCHAR>;