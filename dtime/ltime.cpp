#include <ltime.h>

LTIME::LTIME(){
	time_t Origin = time(NULL) + 28800; // 加28800是把GMT時間調整成台北時間
	
	setHMS(Origin);
}

LTIME::LTIME(int hour, int minute, int second){
	if (hour < 0 || hour > 23) 
		mHour = 0;
	else
		mHour = hour;
	
	if (minute < 0 || minute > 59)
		mMinute = 0;
	else
		mMinute = minute;
	
	if (second < 0 || minute > 59)
		mSecond = 0;
	else
		mSecond = second;
	
	setSeconds();
}

LTIME::LTIME(const LTIME& source){
	mSeconds = source.mSeconds;
	mHour = source.mHour;
	mMinute = source.mMinute;
	mSecond = source.mSecond;
}

string LTIME::toString(void) const{
	char buf[20];
	
	sprintf(buf, "%02d:%02d:%02d", mHour, mMinute, mSecond);
	
	return string(buf);
}

void LTIME::setHMS(time_t Origin){
	int secs = Origin % 86400;
	
	mSeconds = secs;
	
	mHour = secs / 3600;
	secs = secs % 3600;
	
	mMinute = secs / 60;
	mSecond = secs % 60;
}

LTIME LTIME::operator =(const LTIME source){
	mSeconds = source.mSeconds;
	mHour = source.mHour;
	mMinute = source.mMinute;
	mSecond = source.mSecond;
	
	return *this;
}

bool LTIME::operator ==(const LTIME source){
	if (mSeconds == source.mSeconds)
		return true;
	else
		return false;
}

bool LTIME::operator >(const LTIME source){
	if (mSeconds > source.mSeconds)
		return true;
	else
		return false;
}

bool LTIME::operator <(const LTIME source){
	if (mSeconds < source.mSeconds)
		return true;
	else
		return false;
}

int LTIME::operator -(const LTIME other){
	return (mSeconds - other.mSeconds);
}

LTIME LTIME::operator +(const int second){
	LTIME temp(*this);
	int ts = temp.mSecond + second;
	
	calcSecond(temp, ts);
	
	return temp;
}

LTIME LTIME::operator -(const int second){
	LTIME temp(*this);
	int ts = temp.mSecond - second;
	
	calcSecond(temp, ts);
	
	return temp;
}

void LTIME::calcSecond(LTIME& temp, const int second){
	int ts = second;
	
	if (ts >= 0){
		while (ts >= 60){
			temp.mMinute++;
			ts = ts - 60;
		}
		while (temp.mMinute >= 60){
			temp.mHour++;
			temp.mMinute = temp.mMinute - 60;
		}
		while (temp.mHour > 23)
			temp.mHour -= 24;
	} else {
		while (ts < 0){
			temp.mMinute--;
			ts = ts + 60;
		}
		while (temp.mMinute < 0){
			temp.mHour--;
			temp.mMinute = temp.mMinute - 60;
		}
		while (temp.mHour < 0)
	    temp.mHour += 24;
	}
	temp.mSecond = ts;
	temp.setSeconds();
}