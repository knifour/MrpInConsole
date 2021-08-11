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
	
	for (uint32_t s=0; str[s]!=0; s=s+len){
		len = getUtfLength(str[s]);
	  if (len==0)
		  return false;
		
	  for (int i=1; i<len; i++){
		  temp = (str[s+i]>>6)^0x02;
		  if (temp != 0){
			  return false;
			}
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
	  if (temp == 0){
			return -1;
		}
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
	return getFirstDisplayLength((uint8_t*)str.c_str());
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
	return getDisplayLength((uint8_t*)str.c_str());
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

int getMidBytes(const std::string& src, int start, int length){
	return getMidBytes((uint8_t*)src.c_str(), start, length);
}

int getMidBytes(const uint8_t* src, int start, int length){
	int rlen = 0;
	int rbytes = 0;
	int len;
	int ps = 0;
	int bps = 0;
	
	if (start <= 0 || start > countChars(src)){
		return rbytes;
	}
	
	if (length <= 0){
		return rbytes;
	}
	
	if (!isUtf8(src)){
		return -1;
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
		ps = ps + len;
		rbytes = rbytes + len;
		rlen = rlen + 1;
		if (rlen >= length){
			break;
		}
	}
	
	return rbytes;
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
	while (rlen < start && src[ps] != 0){
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
	int rbytes = getMidBytes(src, start, length);
	int rlen;
	
	if (rbytes <= 0)
		return std::string("");
	
	uint8_t* buf = (uint8_t*)malloc(rbytes+1);
	if (buf == NULL)
		return std::string("");
	
	rlen = getMidStr(src, buf, start, length);
	
	if (rlen <= 0){
		free(buf);
		return std::string("");
	}
	else{
		std::string result = std::string((char*)buf);
		free(buf);
		return result;
	}
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

int inStr(const std::string& src, const std::string& dst, int start){
	return inStr((uint8_t*)src.c_str(), (uint8_t*)dst.c_str(), start);
}

int inStr(const uint8_t* src, const uint8_t* target, int start){
	const char* ps;
	int rlen = 1;
	int pt = 0;
	int temp = 0;
	
	if (target[0] == 0)
		return 0;
	
	while (rlen < start && src[pt] != 0){
		temp = getUtfLength(src[pt]);
		rlen = rlen + 1;
		pt = pt + temp;
	}
	
	ps = strstr((char*)&src[pt], (char*)target);
	
	if (ps==NULL)
		return 0;
	
	int len = (int)(ps - (char*)src);
	
	char* buf = (char*)malloc(len+1);
	if (buf == NULL)
		return -1;
	
	for (int i=0; i<len; i++)
		buf[i] = (char)src[i];
	buf[len] = 0;
	
	int pos = countChars(buf) + 1;
	
	free(buf);

	return pos;
}

std::string replaceStr(const std::string& src, const std::string& target, const std::string& replace, bool mode){
  return replaceStr((uint8_t*)src.c_str(), (uint8_t*)target.c_str(), (uint8_t*)replace.c_str(), mode);	
}

std::string replaceStr(const uint8_t* src, const uint8_t* target, const uint8_t* replace, bool mode){
	bool first = true;
	int len, ps, i, targetlen;
	
	std::string result((char*)src);
	len = countChars(result);
	targetlen = countChars(target);
	
	if (len == -1 || targetlen == -1)
		return std::string("");
	
	i = 1;
	ps = 1;
	while (i <= len && ps != 0){
		ps = inStr((uint8_t*)result.c_str(), target, i);
		if (ps != 0){
			result = getLeftStr(result, ps-1) + std::string((char*)replace) + getRightStr(result, len-(ps+targetlen)+1);
      len = countChars(result);			
			if (first){
				first = false;
				if (!mode)
					break;
			}
		}
		i = ps;
	}
	
	return result;
}

}