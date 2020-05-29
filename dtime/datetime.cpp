#include <datetime.h>
#include <stdio.h>

DATETIME::DATETIME(){
	mOrigin = time(NULL)+28800;  // 加28800是把GMT時間調整成台北時間
	getYMD();
	getHMS();
}

DATETIME::DATETIME(int year, int month, int day){
	int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (year < 1970) 
		mYear = 1970;
	else
		mYear = year;
	
	if (month < 1 || month > 12)
		mMonth = 1;
	else
		mMonth = month;
	
	if (isLeap(mYear)) mdays[1] = 29;
	
	if (day < 1 || day > mdays[month-1])
		mDay = 1;
	else
		mDay = day;
	
	mHour = mMinute = mSecond = 0;
	setOrigin();
}

DATETIME::DATETIME(int year, int month, int day, int hour, int minute, int second){
	int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (year < 1970) 
		mYear = 1970;
	else
		mYear = year;
	
	if (month < 1 || month > 12)
		mMonth = 1;
	else
		mMonth = month;
	
	if (isLeap(mYear)) mdays[1] = 29;
	
	if (day > mdays[month-1])
		mDay = 1;
	else
		mDay = day;
	
	if (hour >= 0 && hour <= 23)
		mHour = hour;
	else
		mHour = 0;
	
	if (minute >= 0 && minute <= 59)
		mMinute = minute;
	else
		mMinute = 0;
	
	if (second >= 0 && second <= 59)
		mSecond = second;
	else
		mSecond = 0;
	
	setOrigin();
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

string DATETIME::getTimeString(void){
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
		days = days - yd;
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

void DATETIME::setOrigin(void){
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int sum = 0;
	int lastyear = 0;
	
	if (isLeap(mYear)) days[1] = 29;
	
	lastyear = mYear - 1;
	sum = lastyear*365 + (lastyear/400) - (lastyear/100) + (lastyear/4);
	for (int i=1; i<mMonth; i++) sum = sum + days[i-1];
	sum = sum + mDay;
	
	sum = sum - OLDDAYS;
	mOrigin = (sum*86400) + mHour*3600 + mMinute*60 + mSecond;
}

bool DATETIME::isLeap(int year){
	return (year % 400 == 0) ? true  :
	       (year % 100 == 0) ? false :
	       (year %   4 == 0) ? true  : false;
}

DATETIME DATETIME::operator =(DATETIME source){
	mOrigin = source.mOrigin;
	mYear = source.mYear;
	mMonth = source.mMonth;
	mHour = source.mHour;
	mMinute = source.mMinute;
	mSecond = source.mSecond;
	
	return *this;
}

bool DATETIME::operator ==(DATETIME other){
	if (mOrigin==other.mOrigin)
		return true;
	else
		return false;
}

bool DATETIME::operator >(DATETIME other){
	if (mOrigin>other.mOrigin)
		return true;
	else
		return false;
}

bool DATETIME::operator <(DATETIME other){
	if (mOrigin<other.mOrigin)
		return true;
	else
		return false;
}

int DATETIME::operator -(DATETIME other){
	return (mOrigin-other.mOrigin);
}