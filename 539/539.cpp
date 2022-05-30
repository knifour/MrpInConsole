#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "utf8.h"

#define MAXNUM   39
#define NUMS      5
#define TARGET    0
#define LENGTH   14
#define FILENAME "F539.txt"
#define LASTYEAR 4489

using namespace utf8;

typedef struct stat {
	int No;
	int Cnt;
} STAT;

class LOTTERY{
public:
  static int Cnt;
  int Num[NUMS];
	
	LOTTERY(){
		for (int i=0; i<NUMS; i++)
			Num[i] = 0;
	}
	
	bool setNum(char *data){
		char buf[3];
		int num;
		
		if (strlen(data) != LENGTH)
			return false;
		
		for (int i=0; i<NUMS; i++){
			strncpy(buf, data, 2);
			buf[2] = 0;
			num = stoi(buf);
			if (num < 1 || num > MAXNUM)
				return false;
			Num[i] = num;
			data = data + 3;
		}
		
		return true;
	}
};

int LOTTERY::Cnt = 0;
LOTTERY *n;

void countLottery(void);
void countOdds(void);
void countEvens(void);
void emulateLottery(void);
bool isOdd(int);
bool comp(const STAT&, const STAT&);

STAT lot[MAXNUM];

int main(int argc, char* argv[]){
	ifstream file;
	
	file.open(FILENAME);
	if (!file.is_open()){
		cout << "開檔失敗！" << endl;
		return 1;
	}
	
	int cnt=0;
	char buf[30];
	while (!file.eof()){
		file.getline(buf, sizeof(buf));
		if (strlen(buf) != 0)
			cnt++;
	}
	file.close();
	
	if (cnt == 0){
		cout << "沒有資料！" << endl;
		return 1;
	} else {
		LOTTERY::Cnt = cnt;
	}
	
	n = new LOTTERY[cnt];
	
	file.open(FILENAME);
	for (int i=0; i<cnt; i++){
		file.getline(buf, sizeof(buf));
		if (strlen(buf) == 0)
			break;
	  if (!n[i].setNum(buf)){
			file.close();
			cout << "第" << i << "筆的格式不正確" << endl;
			return 1;
		}
	}
	file.close();
	
	char s=0;
	while (s != '0'){
		cout << "台灣539運彩" << endl;
		cout << "0.結束" << endl;
		cout << "1.開獎統計" << endl;
		cout << "2.單號最大連莊次數" << endl;
		cout << "3.雙號最大連莊次數" << endl;
		cout << "4.模擬下注" << endl;
		cout << "請選擇:";
		cin >> s;
		cout << endl;
		
		switch (s){
		case '1':
		  countLottery();
			break;
			
		case '2':
		  countOdds();
			break;
			
		case '3':
		  countEvens();
			break;
			
		case '4':
		  emulateLottery();
			break;
		}
	}
	
	delete []n;
		
	return 0;
}

void countLottery(void){
	int sum[MAXNUM+1];
	
	for (int i=0; i<MAXNUM+1; i++)
		sum[i] = 0;
	
	for (int i=0; i<LOTTERY::Cnt; i++){
		for (int j=0; j<NUMS; j++){
			sum[n[i].Num[j]]++;
		}
	}
	
	cout << "    001 002 003 004 005 006 007 008 009 010" << endl;
	for (int i=1; i<=MAXNUM; i++){
		if ( (i%10) == 1)
			printf("%03d ", (i-1)/10);
		printf("%03d ", sum[i]);
		if ( (i%10) == 0)
			cout << endl;
	}
	
	cout << endl << endl;
	return;
}

void countOdds(void){
	bool flag = false;
	int cnt = 0;
	int max = 0;
	
	for (int i=0; i<LOTTERY::Cnt; i++){
		if (isOdd(n[i].Num[TARGET])){
			if (!flag){
				cnt = 1;
				flag = true;
			}	else {
				cnt++;
			}
		} else {
			if (cnt > 4)
				printf("連莊數：%2d, 連莊結束總期數：%4d\n", cnt, i);
			if (cnt > max){
				max = cnt;
			}
			cnt = 0;
			flag = false;
		}
	}
	
	cout << "單號最大連莊次數：" << max << endl;
}

void countEvens(void){
	bool flag = false;
	int cnt = 0;
	int max = 0;
	
	for (int i=0; i<LOTTERY::Cnt; i++){
		if (!isOdd(n[i].Num[TARGET])){
			if (!flag){
				cnt = 1;
				flag = true;
			}	else {
				cnt++;
			}
		} else {
			if (cnt > 4)
				printf("連莊數：%2d, 連莊結束總期數：%4d\n", cnt, i);
			if (cnt > max){
				max = cnt;
			}
			cnt = 0;
			flag = false;
		}
	}
	
	cout << "雙號最大連莊次數：" << max << endl;
}

void emulateLottery(void){
	for (int i=0; i<MAXNUM; i++){
		lot[i].No = i+1;
		lot[i].Cnt = 0;
	}

  int temp;	
	for (int i=0; i<LASTYEAR; i++){
		for (int j=0; j<NUMS; j++){
			temp = n[i].Num[j] - 1;
			lot[temp].Cnt++;
		}
	}
	
	sort(lot, lot+MAXNUM, comp);
	for (int i=0; i<MAXNUM; i++){
		printf("%2d => %3d\n", lot[i].No, lot[i].Cnt);
	}
}

bool isOdd(int p){
	if ( (p%2) != 0)
		return true;
	else
		return false;
}

bool comp(const STAT& a, const STAT& b){
	return a.Cnt < b.Cnt;
}