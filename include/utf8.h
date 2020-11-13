#include <stdint.h>
#include <string>

namespace utf8{

// 用途：計算UTF8編碼長度	
// 參數1：UTF8編碼第一碼(uint8_t)
// 回傳值 正數：UTF8編碼長度
//           0：不合法的UTF8編碼(第一碼)
int getCodeLength(uint8_t);

// 用途：判斷是不是合法且完整的UTF8編碼
// 參數1：待判斷字串指標(uint8_t*)
// 回傳值 正數：UTF8編碼長度
//           0：空字串
//          -1：指標位置沒有合法的UTF8編碼
int isUtf8(const uint8_t* str);

// 計算字串的字元數(中文、英文都算1個字)
// 參數1：待計算字串(string&)
// 回傳值 >= 0：字元數
//         = 0：空字串
//          -1：字串內有不合法的UTF8編碼
int countChars(const std::string& str);

// 計算字串的字元數(中文、英文都算1個字)
// 參數1：待計算字串(uint8_t*)
// 回傳值 >= 0：字元數
//         = 0：空字串
//          -1：字串內有不合法的UTF8編碼
int countChars(const uint8_t* str);

// 計算字串的字元數(中文、英文都算1個字)
// 參數1：待計算字串(string&)
// 參數2：UTF8編碼總長度(int&)
// 回傳值 >= 0：字元數
//         = 0：空字串
//          -1：字串內有不合法的UTF8編碼
int countChars(const std::string&, int&);

// 計算字串的字元數(中文、英文都算1個字)
// 參數1：待計算字串(uint8_t*)
// 參數2：UTF8編碼總長度(int&)
// 回傳值 >= 0：字元數
//         = 0：空字串
//          -1：字串內有不合法的UTF8編碼
int countChars(const uint8_t*, int&);
	
}