#include <iostream>
#include <stdio.h>
#include <twindow.h>

TWINDOW::TWINDOW(){
	mParant = NULL;
  mLin = mCol = 0;
  mLINS = 0;
  mCOLS = 0;	
	mFColor = WHITE;
	mBColor = BLACK;
	mError = true;
	mVisible = false;
}

TWINDOW::~TWINDOW(){
}