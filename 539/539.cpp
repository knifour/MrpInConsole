#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include "utf8.h"

using namespace utf8;

class LOTTERY{
public:
  int Num[5];
	
	LOTTERY(){
		for (int i=0; i<5; i++)
			Num[i] = 0;
	}
	
	bool setNum(char *data){
		char buf[3];
		int num;
		
		if (strlen(data) != 14)
			return false;
		
		for (int i=0; i<5; i++){
			strncpy(buf, data, 2);
			buf[2] = 0;
			num = stoi(buf);
			if (num < 1 || num > 39)
				return false;
			Num[i] = num;
			data = data + 3;
		}
		
		return true;
	}
};

LOTTERY *n;

int main(int argc, char* argv[]){
	ifstream file;
	
	file.open("F539.txt");
	if (!file.is_open()){
		cout << "開檔失敗！" << endl;
		return 1;
	}
	
	int cnt=0;
	char buf[20];
	while (!file.eof()){
		file.getline(buf, sizeof(buf));
		if (strlen(buf) != 0)
			cnt++;
	}
	file.close();
	
	if (cnt == 0){
		cout << "沒有資料！" << endl;
		return 1;
	}
	
	n = new LOTTERY[cnt];
	
	file.open("F539.txt");
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
		cout << "1.開獎統計" << endl;
		cout << "2.單號最大連莊次數" << endl;
		cout << "3.雙號最大連莊次數" << endl;
		cout << "0.結束" << endl;
		cout << "請選擇:";
		cin >> s;
		cout << endl;
	}
	
	delete []n;
		
	return 0;
}