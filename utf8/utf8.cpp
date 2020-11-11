#include "utf8.h"

namespace utf8{
	
int getCodeLength(uint8_t code){
  return (code >> 7)   == 0    ? 1 :
	       (code & 0xFC) == 0xFC ? 6 :
	       (code & 0xF8) == 0xF8 ? 5 :
	       (code & 0xF0) == 0xF0 ? 4 :
	       (code & 0xE0) == 0xE0 ? 3 :
	       (code & 0xC0) == 0xC0 ? 2 : 0;
}
	
int isUtf8(const uint8_t* str){
	uint8_t temp;
	int len = getCodeLength(str[0]);
	
	if (len==0)
		return -1;
		
	for (int i=1; i<len; i++){
		temp = (str[i]>>6)^0x02;
		if (temp != 0)
			return -1;
	}
		
	return len;
}
	
bool countChars(const std::string& str, int& len){
  int temp;
  int i = 0;
	uint8_t* buf = (uint8_t*)str.c_str();
		
	len = 0;
 	while (buf[i] != 0){
		temp = isUtf8(&buf[i]);
	  if (temp <= 0)
			return false;
	  len = len + 1;
	  i = i + temp;
  }
	
  return true;
 }
	
bool countChars(uint8_t const* str, int& len){
  int temp;
  int i = 0;
	
 	len = 0;
	while (str[i] != 0){
		temp = isUtf8(&str[i]);
	  if (temp <= 0)
			return false;
	  len = len + 1;
	  i = i + temp;
  }
	
  return true;
}

}