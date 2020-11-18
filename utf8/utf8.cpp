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

bool isUtf8(const std::string& str){
	return isUtf8((uint8_t*)str.c_str());
}
	
bool isUtf8(const uint8_t* str){
	uint8_t temp;
	int len;
	
	for (uint8_t s=0; str[s]!=0; s=s+len){
		len = getUtfLength(str[s]);
	
	  if (len==0)
		  return false;
		
	  for (int i=1; i<len; i++){
		  temp = (str[s+i]>>6)^0x02;
		  if (temp != 0)
			  return false;
	  }
	}
		
	return true;
}
	
int countChars(const std::string& str){
	return countChars((uint8_t*)str.c_str());
}
	
int countChars(uint8_t const* str){
  int temp;
  int i = 0;
	int len = 0;
	
	if (!isUtf8(str))
		return -1;
	
	while (str[i] != 0){
		temp = getUtfLength(str[i]);
	  if (temp == 0)
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
	
	if (!isUtf8(str)){
		codelen = -1;
		return -1;
	}
	
	while (str[i] != 0){
		temp = getUtfLength(str[i]);
	  if (temp == 0)
			return -1;
	  len = len + 1;
	  i = i + temp;
		codelen = codelen + temp;
  }
	
  return len;
}

int getFirstDisplayLength(const std::string& str){
	uint32_t unicode;
	
	if (str[0] == 0)
		return 0;
	
	unicode = fromUtf2Unicode((uint8_t*)str.c_str());
	
	if (unicode==0)
		return -1;
	else
		return isWideChar(unicode) ? 2 : 1;
}

int getFirstDisplayLength(const uint8_t* str){
	uint32_t unicode;
	
	if (str[0] == 0)
		return 0;
	
	unicode = fromUtf2Unicode(str);
	
	if (unicode==0)
		return -1;
	else
		return isWideChar(unicode) ? 2 : 1;
}

int getDisplayLength(const std::string& str){
	int result = 0;
	int len, dlen;
	int i = 0;
	
	if (!isUtf8(str))
		return -1;
	
	while (str[i] != 0){
		len = getUtfLength((uint8_t)str[i]);
		dlen = getFirstDisplayLength((uint8_t*)&str[i]);
		result = result + dlen;
		i = i + len;
	}
	
	return result;
}

int getDisplayLength(const uint8_t* str){
	int result = 0;
	int len, dlen;
	int i = 0;
	
	if (!isUtf8(str))
		return -1;
	
	while (str[i] != 0){
		len = getUtfLength(str[i]);
		dlen = getFirstDisplayLength(&str[i]);
		result = result + dlen;
		i = i + len;
	}
	
	return result;
}

int getMidStr(const std::string& src, uint8_t* dst, int start, int length){
	return getMidStr((uint8_t*)&src[0], dst, start, length);
}

int getMidStr(const uint8_t* src, uint8_t* dst, int start, int length){
	int rlen = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0 || start > countChars(src)){
		dst[bps] = 0;
		return rlen;
	}
	
	if (length <= 0){
		dst[bps] = 0;
		return rlen;
	}
	
	rlen = 1;
	while (rlen < start){
		len = getUtfLength(src[ps]);
		ps = ps + len;
		rlen = rlen + 1;
	}
	
	rlen = 0;
	while (src[ps] != 0){
		len = getUtfLength(src[ps]);
		for (int i=0; i<len; i++){
			dst[bps] = src[ps];
			ps++;
			bps++;
		}
		rlen = rlen + 1;
		if (rlen >= length){
			break;
		}
	}
	dst[bps] = 0;
	
	return rlen;
}

std::string getMidStr(const std::string& src, int start, int length){
	return getMidStr((uint8_t*)&src[0], start, length);
}

std::string getMidStr(const uint8_t* src, int start, int length){
	uint8_t buf[500];
	int rlen = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0 || start > countChars(src)){
		buf[bps] = 0;
		return std::string("");
	}
	
	if (length <= 0){
		buf[bps] = 0;
		return std::string("");
	}
	
	rlen = 1;
	while (rlen < start){
		len = getUtfLength(src[ps]);
		ps = ps + len;
		rlen = rlen + 1;
	}
	
	rlen = 0;
	while (src[ps] != 0){
		len = getUtfLength(src[ps]);
		for (int i=0; i<len; i++){
			buf[bps] = src[ps];
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

int getLeftStr(const std::string& src, uint8_t* dst, int length){
	return getLeftStr((uint8_t*)&src[0], dst, length);
}

int getLeftStr(const uint8_t* src, uint8_t* dst, int length){
	return getMidStr(src, dst, 1, length);
}

std::string getLeftStr(const std::string& src, int length){
	return getLeftStr((uint8_t*)&src[0], length);
}

std::string getLeftStr(const uint8_t* src, int length){
	return getMidStr(src, 1, length);
}

int getRightStr(const std::string& src, uint8_t* dst, int length){
	return getRightStr((uint8_t*)&src[0], dst, length);
}

int getRightStr(const uint8_t* src, uint8_t* dst, int length){
	int rellen = countChars(src);
	
	if (length > rellen)
		length = rellen;
	
	return getMidStr(src, dst, rellen-length+1, length);
}

std::string getRightStr(const std::string& src, int length){
	return getRightStr((uint8_t*)&src[0], length);
}

std::string getRightStr(const uint8_t* src, int length){
	int rellen = countChars(src);
	
	if (length > rellen)
		length = rellen;
	
	return getMidStr(src, rellen-length+1, length);
}

}