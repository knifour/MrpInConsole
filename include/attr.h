#ifndef __ATTR_H
#define __ATTR_H

enum class ATTR: int { /* 需增加編譯條件 -std=c++11 才可以正常編譯 */
	Reset = 0,
	Underline = 4,
	Reverse = 7,
	UnderlineOff = 24,
	ReverseOff = 27,
	FBlack = 30,
	BBlack = 40,
	FRed = 31,
	Bred = 41,
	FGreen = 32,
	BGreen = 42,
	FYellow = 33,
	BYellow = 43,
	FBlue = 34,
	BBlue = 44,
	FMagenta = 35,
	BMagenta = 45,
	FCyan = 36,
	BCyan = 46,
	FWhite = 37,
	BWhite = 47,
	HBlack = 90,
	HRed = 91,
	HGreen = 92,
	HYellow = 93,
	HBlue = 94,
	HMagenta = 95,
	HCyan = 96,
	HWhite = 97
};

#endif