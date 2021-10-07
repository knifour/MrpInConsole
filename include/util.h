#ifndef __UTIL_H
#define __UTIL_H

#include <string>
#include <stdint.h>
#include <sys/select.h>
#include <termios.h>
#include <sys/ioctl.h>
#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include <wide.h>

using namespace std;

/* 初始化Termios，傳入0可抑制按鍵顯示在螢幕上，程式結束前務必使用resetTermios恢復按鍵顯示 */
void initTermios(int);

/* 若有使用initTermios抑制按鍵顯示，結束前務必呼叫此函式 */
void resetTermios(void);

/* 偵測是否有按鍵輸入(不會等待使用者按鍵)，回傳值為等待讀取的按鍵數 */
/* 如果不希望使用者的按鍵顯示在螢幕上，務必呼叫initTermios(0)抑制螢幕輸出 */
/* 結束後務必呼叫resetTermios()恢復螢幕輸出 */
int _kbhit(void);

/* 以_kbhit偵測到使用者按鍵後，以此函式讀取使用者按鍵值，並以string的形式回傳按鍵值 */
/* 傳入值為以_kbhit偵測到的按鍵數量 */
string getKeycode(int);

/* 等待使用者輸入按鍵 */
/* 若傳回true表示傳址參數string回傳值為特殊按鍵    */
/* 若傳回false表示傳址參數string回傳值為該按鍵字元 */
bool inKey(string&);

/* 等待輸入，不顯示輸入字元 */
char getch(void); 

/* 等待輸入，顯示輸入字元 */
char getche(void); 

/* 等待輸入，不顯示輸入字元，會處理特殊鍵 */
/* char input(int&); */

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