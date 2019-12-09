#include <iostream>
#include <termios.h>
#include <stdio.h>
#include <util.h>

static struct termios old, current;

void initTermios(int echo){
	tcgetattr(0, &old);
	current = old;
	current.c_lflag &= !ICANON;
	if (echo){
		current.c_lflag &= ~ECHO;
	}
	tcsetattr(0, TCSANOW, &current);
}

void resetTermios(void){
	tcsetattr(0, TCSANOW, &old);
}

char getch_(int echo){
	char ch;
	initTermios(echo);
	ch = getchar();
	resetTermios();
	return ch;
}

char getch(void){
	return getch_(0);
}

char getche(void){
	return getch_(1);
}

int Utf8Len(std::string const &utf8){
	uint8_t first_byte = (uint8_t)utf8[0];
	int len =
	  (first_byte >> 7) == 0 ? 1 :
		(first_byte & 0xF0) == 0xF0 ? 4 :
		(first_byte & 0xE0) == 0xE0 ? 3 :
		(first_byte & 0xC0) == 0xC0 ? 2 : 0;
	
	return len;
}

int Utf8Len(uint8_t const *utf8){
	uint8_t first_byte = utf8[0];
	int len =
	  (first_byte >> 7) == 0 ? 1 :
		(first_byte & 0xF0) == 0xF0 ? 4 :
		(first_byte & 0xE0) == 0xE0 ? 3 :
		(first_byte & 0xC0) == 0xC0 ? 2 : 0;
	
	return len;
}

int Utf8Len(char first_byte){
	int len =
	  (first_byte >> 7) == 0 ? 1 :
		(first_byte & 0xF0) == 0xF0 ? 4 :
		(first_byte & 0xE0) == 0xE0 ? 3 :
		(first_byte & 0xC0) == 0xC0 ? 2 : 0;
	
	return len;
}

int Utf8DLen(std::string const &utf8){
	uint32_t unicode = 0;
	uint8_t first_byte = (uint8_t)utf8[0];
	uint8_t len = 
	  (first_byte >> 7) == 0 ? 1 :
		(first_byte & 0xF0) == 0xF0 ? 4 :
		(first_byte & 0xE0) == 0xE0 ? 3 :
		(first_byte & 0xC0) == 0xC0 ? 2 : 0;
	
	unicode += (uint8_t)(first_byte << len) >> len;
	for (uint8_t i=1; i<len; i++){
		unicode <<= 6;
		unicode += ((uint8_t)utf8[i]) & 0x3F;
	}
	
	if (unicode >= (uint32_t)0x2500 && unicode <= (uint32_t)0x257F){
		return 2;
	} else if (unicode >= (uint32_t)0x4E00 && unicode <= (uint32_t)0x9FFF){
		return 2;
	}
	
	return 1;
}

int Utf8DLen(uint8_t const *utf8){
	uint32_t unicode = 0;
	uint8_t first_byte = utf8[0];
	uint8_t len = 
	  (first_byte >> 7) == 0 ? 1 :
		(first_byte & 0xF0) == 0xF0 ? 4 :
		(first_byte & 0xE0) == 0xE0 ? 3 :
		(first_byte & 0xC0) == 0xC0 ? 2 : 0;
	
	unicode += (uint8_t)(first_byte << len) >> len;
	for (uint8_t i=1; i<len; i++){
		unicode <<= 6;
		unicode += (utf8[i]) & 0x3F;
	}
	
	if (unicode >= (uint32_t)SEC0_LOW && unicode <= (uint32_t)SEC0_HIGH){
		return 2;
	} else if (unicode >= (uint32_t)SEC1_LOW && (uint32_t)SEC2_HIGH){
		return 2;
  } else if (unicode >= (uint32_t)SEC2_LOW && unicode <= (uint32_t)SEC2_HIGH){
		return 2;
	} else if (unicode >= (uint32_t)SEC3_LOW && unicode <= (uint32_t)SEC3_HIGH){
		return 2;
	}
	
	return 1;
}

int FromUtf8(std::string const &utf8, char *buf){
	int len;
	
	len = Utf8Len(utf8);
	for (int i=0; i<len; i++){
		buf[i] = (char)utf8[i];
	}
	buf[len] = 0;
	
	return len;
}

int Utf8RealLen(uint8_t const *utf8){
	int result = 0;
	int len;
	int i = 0;
	
	while (utf8[i] != 0){
		len = Utf8Len(utf8[i]);
		result = result + 1;
		i = i + len;
	}
	
	return result;
}

int Utf8RealLen(std::string const &utf8){
	int result = 0;
	int len;
	int i = 0;
	
	while (utf8[i] != 0){
		len = Utf8Len(utf8[i]);
		result = result + 1;
		i = i + len;
	}
	
	return result;
}

int Utf8RealDLen(uint8_t const *utf8){
	int result = 0;
	int len, dlen;
	int i = 0;
	
	while (utf8[i] != 0){
		len = Utf8Len(utf8[i]);
		dlen = Utf8DLen(&utf8[i]);
		result = result + dlen;
		i = i + len;
	}
	
	return result;
}

int Utf8RealDLen(std::string const &utf8){
	int result = 0;
	int len, dlen;
	int i = 0;
	
	while (utf8[i] != 0){
		len = Utf8Len(utf8[i]);
		dlen = Utf8DLen((uint8_t*)&utf8[i]);
		result = result + dlen;
		i = i + len;
	}
	
	return result;
}

int Utf8Mid(uint8_t const *utf8, uint8_t *buf, int start, int length){
	int rlen = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0){
		buf[bps] = 0;
		return rlen;
	}
	
	if (length <= 0){
		buf[bps] = 0;
		return rlen;
	}
	
	rlen = Utf8RealLen(utf8);
	if (start > rlen){
		buf[bps] = 0;
		return rlen;
	}
	
	rlen = 1;
	while (rlen < start){
		len = Utf8Len(utf8[ps]);
		ps = ps + len;
		rlen = rlen + 1;
	}
	
	rlen = 0;
	while (utf8[ps] != 0){
		len = Utf8Len(utf8[ps]);
		for (int i=0; i<len; i++){
			buf[bps] = utf8[ps];
			ps++;
			bps++;
		}
		rlen = rlen + 1;
		if (rlen >= length){
			break;
		}
	}
	buf[bps] = 0;
	
	return rlen;
}

std::string Utf8Mids(uint8_t const *utf8, int start, int length){
	uint8_t buf[500];
	int rlen = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0){
		buf[bps] = 0;
		return std::string("");
	}
	
	if (length <= 0){
		buf[bps] = 0;
		return std::string("");
	}
	
	rlen = Utf8RealLen(utf8);
	if (start > rlen){
		buf[bps] = 0;
		return std::string("");
	}
	
	rlen = 1;
	while (rlen < start){
		len = Utf8Len(utf8[ps]);
		ps = ps + len;
		rlen = rlen + 1;
	}
	
	rlen = 0;
	while (utf8[ps] != 0){
		len = Utf8Len(utf8[ps]);
		for (int i=0; i<len; i++){
			buf[bps] = utf8[ps];
			ps++;
			bps++;
		}
		rlen = rlen + 1;
		if (rlen >= length){
			break;
		}
	}
	buf[bps] = 0;
	
	return std::string((char*)buf);
}