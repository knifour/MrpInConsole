#include <date.h>

DATE::DATE(){
	time_t Origin = time(NULL) + 28800; // 加28800是把GMT時間調整成台北時間
	
	setYMD(Origin);
	setDays();
}

DATE::DATE(int year, int month, int day){
	if (year < 1) 
		mYear = 1;
	else
		mYear = year;
	
	if (month < 1 || month > 12)
		mMonth = 1;
	else
		mMonth = month;
	
	if (isLeap(mYear)) 
		MONTHDAY[1] = 29;
	else
		MONTHDAY[1] = 28;
	
	if (day < 1 || day > MONTHDAY[month-1])
		mDay = 1;
	else
		mDay = day;
	
	setDays();
}

DATE::DATE(const DATE& source){
	mDays = source.mDays;
	mYear = source.mYear;
	mMonth = source.mMonth;
	mDay = source.mDay;
}

DATE::DATE(const DATETIME& source){
	mYear = source.getYear();
	mMonth = source.getMonth();
	mDay = source.getDay();
	setDays();
}

string DATE::toString(int mode) const{
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
	int days = Origin / 86400 + 1;
	mYear = 1970;
	int yd = 365;
	while (days > yd){
		mYear++;
		days = days - yd;
		yd = isLeap(mYear) ? 366 : 365;
	}
	
	if (isLeap(mYear)) 
		MONTHDAY[1] = 29;
	else
		MONTHDAY[1] = 28;
	
	mMonth = 1;
	while (days > MONTHDAY[mMonth-1]){
		days = days - MONTHDAY[mMonth-1];
		mMonth++;
	}
	mDay = days;
}

void DATE::setDays(void){
	int lastyear = 0;
	
	if (isLeap(mYear)) 
		MONTHDAY[1] = 29;
	else
		MONTHDAY[1] = 28;
	
	lastyear = mYear - 1;
	mDays = lastyear*365 + (lastyear/400) - (lastyear/100) + (lastyear/4);
	for (int i=1; i<mMonth; i++) mDays = mDays + MONTHDAY[i-1];
	mDays = mDays + mDay;
}

DATE DATE::operator =(const DATE source){
	mDays = source.mDays;
	mYear = source.mYear;
	mMonth = source.mMonth;
	mDay = source.mDay;
	
	return *this;
}

DATE DATE::operator =(const DATETIME source){
	mYear = source.getYear();
	mMonth = source.getMonth();
	mDay = source.getDay();
	setDays();
	
	return *this;
}

int DATE::operator -(const DATE other){
	return (mDays - other.mDays);
}

DATE DATE::operator +(const int day){
	DATE temp(*this);
	int td = temp.mDay + day;
	
	calcDay(temp, td);
	
	return temp;
}

DATE DATE::operator -(const int day){
	DATE temp(*this);
	int td = temp.mDay - day;
	
	calcDay(temp, td);
	
	return temp;
}

void DATE::calcDay(DATE& temp, const int day){
	if (isLeap(temp.mYear)) 
		MONTHDAY[1] = 29;
	else
		MONTHDAY[1] = 28;
	
	int td = day;
	
	if (td >= 0){
	  while (td > MONTHDAY[temp.mMonth-1]){
			td = td - MONTHDAY[temp.mMonth-1];
			temp.mMonth++;
			if (temp.mMonth > 12){
				temp.mYear++;
				temp.mMonth = 1;
				if (isLeap(temp.mYear)) 
					MONTHDAY[1] = 29;
				else
					MONTHDAY[1] = 28;
			}
		}
	} else {
		while (td <= 0){
			temp.mMonth--;
			if (temp.mMonth <= 0){
				temp.mYear--;
				temp.mMonth = 12;
				if (isLeap(temp.mYear))
					MONTHDAY[1] = 29;
				else
					MONTHDAY[1] = 28;
			}
			td = td + MONTHDAY[temp.mMonth-1];
		}
	}
	temp.mDay = td;
	temp.setDays();
}