#include <stdint.h>
#include <string>
#include <stdio.h>
#include "util.h"

namespace utf8{

// 用途：計算UTF8編碼長度	
// 參數1：UTF8編碼第一碼(uint8_t)
// 回傳值 > 0：UTF8編碼長度
//        = 0：不合法的UTF8編碼(第一碼)
int getUtfLength(uint8_t);

// 用途：計算UTF8編碼長度	
// 參數1：unicode編碼(uint32_t)
// 回傳值 > 0：UTF8編碼長度
//        = 0：不合法的unicode編碼
int getUtfLength(uint32_t);

// 用途：將UTF8編碼轉換成unicode編碼
// 參數：UTF8編碼位址(uint8_t&)
// 回傳值 > 0：轉換後的unicode編碼
//        = 0：不合法的UTF8編碼
uint32_t fromUtf2Unicode(const uint8_t*);

// 用途：判斷字串內容是不是合法的UTF8編碼
// 參數1：待判斷字串指標(string&)
// 回傳值 > 0：UTF8編碼長度
//        = 0：空字串
//        =-1：指標位置沒有合法的UTF8編碼
bool isUtf8(const std::string&);

// 用途：判斷字串內容是不是合法的UTF8編碼
// 參數1：待判斷字串指標(uint8_t*)
// 回傳值 > 0：UTF8編碼長度
//        = 0：空字串
//        =-1：指標位置沒有合法的UTF8編碼
bool isUtf8(const uint8_t*);

// 計算字串的字元數(中文、英文都算1個字)
// 參數1：待計算字串(string&)
// 回傳值 >= 0：字元數
//         = 0：空字串
//         =-1：字串內有不合法的UTF8編碼
int countChars(const std::string&);

// 計算字串的字元數(中文、英文都算1個字)
// 參數1：待計算字串(uint8_t*)
// 回傳值 >= 0：字元數
//         = 0：空字串
//          -1：字串內有不合法的UTF8編碼
int countChars(const uint8_t*);

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
//        =-1：不合法的UTF8編碼
int getFirstDisplayLength(const std::string&);

// 取得字串第一個字的顯示寬度
// 參數：字串(uint8_t*)
// 回傳值 = 2：寬字元
//        = 1：一般字元
//        = 0：空字串
//        =-1：不合法的UTF8編碼
int getFirstDisplayLength(const uint8_t*);

// 取得字串的顯示寬度
// 參數：字串(string&)
// 回傳值 > 0：字串顯示寬度
//        = 0：空字串
//        =-1：字串含有不合法的UTF8編碼
int getDisplayLength(const std::string&);

// 取得字串的顯示寬度
// 參數：字串(uint8_t*)
// 回傳值 > 0：字串顯示寬度
//        = 0：空字串
//        =-1：字串含有不合法的UTF8編碼
int getDisplayLength(const uint8_t*);

// 攫取UTF8中間字串
// 參數1：原始字串(string&)
// 參數2：攫取到的字串會放在這裡(結尾自動補0)，呼叫者須自行準備足夠的記憶體空間
// 參數3：起始位置(以字元為單位，中英文都算1個字)
// 參數4：攫取長度
// 回傳值：實際攫取的字元數
int getMidStr(const std::string&, uint8_t*, int, int);

// 攫取UTF8中間字串
// 參數1：原始字串(uint8_t*)
// 參數2：攫取到的字串會放在這裡(結尾自動補0)，呼叫者須自行準備足夠的記憶體空間
// 參數3：起始位置(以字元為單位，中英文都算1個字)
// 參數4：攫取長度
// 回傳值：實際攫取的字元數
int getMidStr(const uint8_t*, uint8_t*, int, int);

// 攫取UTF8中間字串，以string型式回傳攫取到的字串
// 警告：緩衝取只有500 BYTES，欲擷取字串的編碼總長度不可超過499 BYTES
// 參數1：原始字串(string&)
// 參數2：起始位置(以字元為單位，中英文都算1個字)
// 參數3：攫取長度
// 回傳值：攫取的字串
std::string getMidStr(const std::string&, int, int);

// 攫取UTF8中間字串，以string型式回傳攫取到的字串
// 警告：緩衝取只有500 BYTES，欲擷取字串的編碼總長度不可超過499 BYTES
// 參數1：原始字串(uint8_t*)
// 參數2：起始位置(以字元為單位，中英文都算1個字)
// 參數3：攫取長度
// 回傳值：攫取的字串
std::string getMidStr(const uint8_t*, int, int);
	
}