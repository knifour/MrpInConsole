#include "utf8.h"

namespace utf8{
	
int getUtfLength(uint8_t code){
  return (code >> 7)   == 0    ? 1 :
	       (code & 0xFC) == 0xFC ? 6 :
	       (code & 0xF8) == 0xF8 ? 5 :
	       (code & 0xF0) == 0xF0 ? 4 :
	       (code & 0xE0) == 0xE0 ? 3 :
	       (code & 0xC0) == 0xC0 ? 2 : 0;
}

int getUtfLength(uint32_t code){
  return (code <= 0x7F)      ? 1 :
	       (code <= 0x7FF)     ? 2 :
				 (code <= 0xFFFF)    ? 3 :
				 (code <= 0x1FFFFF)  ? 4 :
				 (code <= 0x3FFFFFF) ? 5 :
				 (code <= 0x7FFFFFF) ? 6 : 0;
}

uint32_t fromUtf2Unicode(const uint8_t* utf){
	uint32_t unicode = 0;
	uint32_t mask = 0xFF;
	int len = getUtfLength(utf[0]);
	
	if (len == 0)
		return 0;
	unicode = ((utf[0] << len) & mask) >> len;
	for (int i=1; i<len; i++){
		if (((utf[i]>>6)^0x02) != 0)
			return 0;
		unicode <<= 6;
		unicode += (utf[i] & 0x3F);
	}
	
	return unicode;
}
	
int isUtf8(const uint8_t* str){
	uint8_t temp;
	int len = getUtfLength(str[0]);
	
	if (len==0)
		return -1;
		
	for (int i=1; i<len; i++){
		temp = (str[i]>>6)^0x02;
		if (temp != 0)
			return -1;
	}
		
	return len;
}
	
int countChars(const std::string& str){
	return countChars((uint8_t*)str.c_str());
}
	
int countChars(uint8_t const* str){
  int temp;
  int i = 0;
	int len = 0;
	
	while (str[i] != 0){
		temp = isUtf8(&str[i]);
	  if (temp < 0)
			return -1;
	  len = len + 1;
	  i = i + temp;
  }
	
  return len;
}

int countChars(const std::string& str, int& codelen){
	return countChars((uint8_t*)str.c_str(), codelen);
}

int countChars(const uint8_t* str, int& codelen){
  int temp;
  int i = 0;
	int len = 0;
	
	codelen = 0;
	while (str[i] != 0){
		temp = isUtf8(&str[i]);
	  if (temp < 0)
			return -1;
	  len = len + 1;
	  i = i + temp;
		codelen = codelen + temp;
  }
	
  return len;
}

int getFirstDisplayLength(const std::string& str){
	uint8_t* utf = (uint8_t*)str.c_str();
	
	if (utf[0] == 0)
		return 0;
	
	return isWideChar(fromUtf2Unicode(utf)) ? 2 : 1;
}

int getFirstDisplayLength(const uint8_t* str){
	if (str[0] == 0)
		return 0;
	
	return isWideChar(fromUtf2Unicode(str)) ? 2 : 1;
}

}