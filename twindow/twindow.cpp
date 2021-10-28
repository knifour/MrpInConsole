#include <iostream>
#include <stdio.h>
#include <twindow.h>

template<class T> TWINDOW<T>::TWINDOW(){
	mTerminal = nullptr;
	mParant = nullptr;
  mLin = mCol = 1;
  mLINS = 0;
  mCOLS = 0;	
	mFColor = ATTR::WHITE;
	mBColor = ATTR::BLACK;
	mUnderline = false;
	mError = true;
}

template<class T> void TWINDOW<T>::createBuffer(void){
	if (mError)
		return;
	
	if (mLINS<1){
		mError = true;
		return;
	}
	
	if (mCOLS<1){
		mError = true;
		return;
	}
  
	TWindowBuf = new T*[mLINS];
	for (int i=0; i<mLINS; i++)
		TWindowBuf[i] = new T[mCOLS];
}

template<class T> TWINDOW<T>::~TWINDOW(){
	for (int i=0; i<mLINS; i++)
		delete[] TWindowBuf[i];
	
	delete[] TWindowBuf;
}

template class TWINDOW<UTF8SCHAR>;