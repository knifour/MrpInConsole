#ifndef __UTIL_H
#define __UTIL_H

#define SEC0_LOW  0x2500  /* 定義寬字元Unicode碼區段0下限 */
#define SEC0_HIGH 0x257F  /* 定義寬字元Unicode碼區段0上限 */
#define SEC1_LOW  0x2E80  /* 定義寬字元Unicode碼區段1下限 */
#define SEC1_HIGH 0xA4FF  /* 定義寬字元Unicode碼區段1上限 */
#define SEC2_LOW  0xAC00  /* 定義寬字元Unicode碼區段2下限 */
#define SEC2_HIGH 0xD7FF  /* 定義寬字元Unicode碼區段2上限 */
#define SEC3_LOW  0xF900  /* 定義寬字元Unicode碼區段3下限 */
#define SEC3_HIGH 0xFFFD  /* 定義寬字元Unicode碼區段3上限 */

#include <string>
#include <stdint.h>
#include <keypad.h>

char getch(void);  /* 等待輸入，不顯示輸入字元 */
char getche(void); /* 等待輸入，顯示輸入字元 */
void cursor(bool); /* 顯示或隱藏游標 */
void CurPos(int&, int&); /* 取得游標位置 */
char input(int&);  /* 等待輸入，不顯示輸入字元，會處理特殊鍵 */

/* 計算UTF8 BYTE STREAM長度(只判斷傳入字串的第一個字元) */
int Utf8Len(std::string const &utf8);
int Utf8Len(uint8_t const *utf8);
int Utf8Len(char first_byte);

/* 計算UTF8字元的顯示長度(只判斷傳入字串的第一個字元) */
int Utf8DLen(std::string const &utf8);
int Utf8DLen(uint8_t const *utf8);

int FromUtf8(std::string const &utf8, char *buf);

/* 計算字串字數，無論中文、英文都算1個字 */
int Utf8RealLen(uint8_t const *utf8);
int Utf8RealLen(std::string const &utf8);

/* 計算UTF8字串的總顯示長度 */
int Utf8RealDLen(uint8_t const *utf8);
int Utf8RealDLen(std::string const &utf8);

int Utf8Mid(uint8_t const *utf8, uint8_t *buf, int start, int length);
std::string Utf8Mids(uint8_t const *utf8, int start, int length);

#endif