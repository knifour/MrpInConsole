#include <iostream>
#include <stdio.h>
#include <twindow.h>
#include <utf8schar.h>

template<class T> TWINDOW<T>::TWINDOW(){
	mParant = nullptr;
  mLin = mCol = 0;
  mLINS = 0;
  mCOLS = 0;	
	mFColor = WHITE;
	mBColor = BLACK;
	mUnderline = false;
	mError = true;
}

template<class T> TWINDOW<T>::TWINDOW(TWINDOW* p1, const char* p2){
	mParant = p1;
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