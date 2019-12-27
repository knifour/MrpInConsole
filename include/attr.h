#ifndef __ATTR_H
#define __ATTR_H

enum ATTR: int { /* 需增加編譯條件 -std=c++11 才可以正常編譯 */
	BLACK    =  0,
	RED      =  1,
	GREEN    =  2,
	YELLOW   =  3,
	BLUE     =  4,
	MAGENTA  =  5,
	CYAN     =  6,
	WHITE    =  7,
	HBLACK   =  8,
	HRED     =  9,
	HGREEN   = 10,
	HYELLOW  = 11,
	HBLUE    = 12,
	HMAGENTA = 13,
	HCYAN    = 14,
	HWHITE   = 15
};

#endif