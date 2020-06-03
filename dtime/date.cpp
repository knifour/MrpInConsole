#include <date.h>

DATE::DATE(){
	time_t Origin = time(NULL) + 28800; // 加28800是把GMT時間調整成台北時間
	
	setYMD(Origin);
	setDays();
}

DATE::DATE(int year, int month, int day){
	int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (year < 1) 
		mYear = 1;
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
	
	setDays();
}

DATE::DATE(DATE& source){
	mDays = source.mDays;
	mYear = source.mYear;
	mMonth = source.mMonth;
	mDay = source.mDay;
}

DATE::DATE(DATETIME& source){
	mYear = source.getYear();
	mMonth = source.getMonth();
	mDay = source.getDay();
	setDays();
}

string DATE::toString(int mode){
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

void DATE::setYMD(time_t Origin){
	int mdays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	int days = Origin / 86400 + 1;
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

void DATE::setDays(void){
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int lastyear = 0;
	
	if (isLeap(mYear)) days[1] = 29;
	
	lastyear = mYear - 1;
	mDays = lastyear*365 + (lastyear/400) - (lastyear/100) + (lastyear/4);
	for (int i=1; i<mMonth; i++) mDays = mDays + days[i-1];
	mDays = mDays + mDay;
}

bool DATE::isLeap(int year){
	return (year % 400 == 0) ? true  :
	       (year % 100 == 0) ? false :
	       (year %   4 == 0) ? true  : false;
}

DATE DATE::operator =(DATE source){
	mDays = source.mDays;
	mYear = source.mYear;
	mMonth = source.mMonth;
	mDay = source.mDay;
	
	return *this;
}

DATE DATE::operator =(DATETIME source){
	mYear = source.getYear();
	mMonth = source.getMonth();
	mDay = source.getDay();
	setDays();
	
	return *this;
}

int DATE::operator -(DATE other){
	return (mDays - other.mDays);
}

DATE DATE::operator +(int day){
	DATE temp(*this);
	int td = temp.mDay + day;
	
	int days[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
	if (isLeap(temp.mYear)) days[1] = 29;
	
	if (td >= 0){
	  while (td > days[temp.mMonth-1]){
			td = td - days[temp.mMonth-1];
			temp.mMonth++;
			if (temp.mMonth > 12){
				temp.mYear++;
				temp.mMonth = 1;
				if (isLeap(temp.mYear)) days[1] = 29;
			}
		}
	} else {
		while (td < 0){
			temp.mMonth--;
			if (temp.mMonth < 0){
				temp.mYear--;
				temp.mMonth = 12;
				if (isLeap(temp.mYear)) days[1] = 29;
			}
			td = td + days[temp.mMonth-1];
		}
	}
	temp.mDay = td;
	setDays();
	return temp;
}