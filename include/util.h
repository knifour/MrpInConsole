#ifndef __UTIL_H
#define __UTIL_H

#include <string>
#include <stdint.h>
#include <keypad.h>
#include <iconv.h>
#include <stdio.h>
#include <string.h>

#define SEC0_LOW  ((uint32_t)0x2500)   /* 定義CJK寬字元區段開始 */
#define SEC0_HIGH ((uint32_t)0x257F)  
#define SEC1_LOW  ((uint32_t)0x2E80)  
#define SEC1_HIGH ((uint32_t)0x9FFF)  
#define SEC2_LOW  ((uint32_t)0xAC00)  
#define SEC2_HIGH ((uint32_t)0xD7AF)  
#define SEC3_LOW  ((uint32_t)0xF900)  
#define SEC3_HIGH ((uint32_t)0xFA6D)  
#define SEC4_LOW  ((uint32_t)0xFF01)
#define SEC4_HIGH ((uint32_t)0xFF5E)
#define SEC5_LOW  ((uint32_t)0xFFE0)
#define SEC5_HIGH ((uint32_t)0xFFE6)
#define SEC6_LOW  ((uint32_t)0x1D300)
#define SEC6_HIGH ((uint32_t)0x1D35F)
#define SEC7_LOW  ((uint32_t)0x20000)
#define SEC7_HIGH ((uint32_t)0x2EBEF)
#define SEC8_LOW  ((uint32_t)0x2F800)
#define SEC8_HIGH ((uint32_t)0x2FA1F) /* 定義CJK寬字元區段結束 */

/* 等待輸入，不顯示輸入字元 */
char getch(void); 

/* 等待輸入，顯示輸入字元 */
char getche(void); 

/* 等待輸入，不顯示輸入字元，會處理特殊鍵 */
char input(int&);  

/* 顯示游標 */
void showCursor(void); 

/* 隱藏游標 */
void hideCursor(void); 

/* 取得游標位置 */
void getCursorPos(int&, int&); 

/* 傳入西元年份，判斷該年度是否為閏年 */
bool isLeap(int);  

/* 動態二維陣列 */
void* new2D(int h, int w, int size); 

/* 動態二維陣列巨集，使用者傳入二維陣列大小及型態即可建立 */
/* 使用者以指指標形式接收動態配置記憶體 */
/* 使用者須以delete []指令刪除動態配置的記憶體 */
#define NEW2D(H, W, TYPE) (TYPE **)new2D(H, W, sizeof(TYPE))

/* 計算UTF8 BYTE STREAM長度(只判斷傳入字串的第一個字元) */
int getFirstCharBytesU8(const std::string& utf8);
int getFirstCharBytesU8(const uint8_t* utf8);
int getFirstCharBytesU8(char first_byte);

// 計算UTF8編碼長度, 以unsigned char為參數傳入函數即可計算
int getUtfLengthU8(uint8_t first_byte);

/* 計算UTF8字元的顯示長度(只判斷傳入字串的第一個字元) */
int getFirstDLenU8(const std::string& utf8);
int getFirstDLenU8(const uint8_t* utf8);

/* 根據unicode值判斷是否為寬字元 */
bool isWideChar(uint32_t);

int FromUtf8(std::string const &utf8, char *buf);

/* 計算字串字數，無論中文、英文都算1個字 */
int getCharsU8(uint8_t const *utf8);
int getCharsU8(std::string const &utf8);

/* 計算UTF8字串的總顯示長度 */
int getDLenU8(uint8_t const *utf8);
int getDLenU8(std::string const &utf8);

int Utf8Mid(uint8_t const *utf8, uint8_t *buf, int start, int length);
std::string Utf8Mids(uint8_t const *utf8, int start, int length);

/* 將Big5編碼的Byte Stream轉換成Utf8編碼的Byte Stream */
std::string convertBig5toUtf8(char *src, int *status);
std::string convertBig5toUtf8(std::string src, int *status);

#endif