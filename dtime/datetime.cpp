#include <datetime.h>
#include <stdio.h>

DATETIME::DATETIME(){
	mOrigin = time(NULL)+28800;
	getYMD();
	getHMS();
}

string DATETIME::getDateString(int mode){
	char buf[20];
	
	switch (mode){
	case 0:
	  sprintf(buf, "%04d/%02d/%02d", mYear, mMonth, mDay);
		break;
		
	case 1:
	  sprintf(buf, "%04d%02d%02d", mYear, mMonth, mDay);
		break;
		
	case 2:
		sprintf(buf, "%03d/%02d/%02d", mYear-1911, mMonth, mDay);
		break;
		
	case 3:
	  sprintf(buf, "%03d%02d%02d", mYear-1911, mMonth, mDay);
		break;
		
	};
	
	return string(buf);
}

string DATETIME::getTimeString(int mode){
	char buf[20];
	
	sprintf(buf, "%02d:%02d:%02d", mHour, mMinute, mSecond);
	return string(buf);
}

void DATETIME::getYMD(void){
	int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	int days = mOrigin / 86400 + 1;
	mYear = 1970;
	int yd = 365;
	while (days > yd){
		mYear++;
		days = days -yd;
		yd = isLeap(mYear) ? 366 : 365;
	}
	
	if (isLeap(mYear)) mdays[1] = 29;
	mMonth = 1;
	while (days > mdays[mMonth-1]){
		days = days - mdays[mMonth-1];
		mMonth++;
	}
	mDay = days;
}

void DATETIME::getHMS(void){
	int secs = mOrigin % 86400;
	
	mHour = secs / 3600;
	secs = secs - (mHour * 3600);
	mMinute = secs / 60;
	mSecond = secs - (mMinute * 60);
}

bool DATETIME::isLeap(int year){
	return (year % 400 == 0) ? true  :
	       (year % 100 == 0) ? false :
	       (year %   4 == 0) ? true  : false;
}