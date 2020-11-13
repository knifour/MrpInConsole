#include <stdint.h>
#include <string>
#include <stdio.h>
#include "util.h"

namespace utf8{

// 用途：計算UTF8編碼長度	
// 參數1：UTF8編碼第一碼(uint8_t)
// 回傳值 正數：UTF8編碼長度
//           0：不合法的UTF8編碼(第一碼)
int getUtfLength(uint8_t);

// 用途：計算UTF8編碼長度	
// 參數1：unicode編碼(uint32_t)
// 回傳值 正數：UTF8編碼長度
//           0：不合法的unicode編碼
int getUtfLength(uint32_t);

// 用途：將UTF8編碼轉換成unicode編碼
// 參數：UTF8編碼位址(uint8_t&)
// 回傳值：轉換後的unicode編碼，回傳0代表此參數為不合法的UTF8編碼
uint32_t fromUtf2Unicode(const uint8_t* utf);

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

// 取得字串第一個字的顯示寬度
// 參數：字串(string&)
// 回傳值 = 2：寬字元
//        = 1：一般字元
//        = 0：空字串
int getFirstDisplayLength(const std::string&);

// 取得字串第一個字的顯示寬度
// 參數：字串(uint8_t*)
// 回傳值 = 2：寬字元
//        = 1：一般字元
//        = 0：空字串
int getFirstDisplayLength(const uint8_t*);
	
}