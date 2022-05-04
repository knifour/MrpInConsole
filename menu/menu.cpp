#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "utf8.h"

using namespace utf8;

bool readMenuData();

fstream json;
string menuitem[10][20][3];

int main(int argc, char* argv[]){
	int lin, pos;
	int width, spc, num;
	
	if (argc!=6){
		cout << "參數數量錯誤" << endl;
		cout << "格式" << endl;
		cout << "menu 起始列 起始行 字元數 間隔 數量" << endl;
		return 1;
	}
	
	lin = atoi(argv[1]);
	pos = atoi(argv[2]);
	width = atoi(argv[3]);
	spc = atoi(argv[4]);
	num = atoi(argv[5]);
	
	ifstream mf;
	mf.open("menu.scr", ios::in);
	if (!mf){
		cout << "開啟menu.scr失敗" << endl;
		return 1;
	}
	
	char buf[101];
	char item[20];
	int status, sp, dp;
	string name;
	
	do {
    for (int i=0; i<(lin-1); i++){
			mf.getline(buf, sizeof(buf));
			if (mf.eof()){
				cout << "menu.scr不是menu檔" << endl;
				return 1;
			}
		}	
		mf.getline(buf, sizeof(buf));
		mf.close();
		break;
	} while (!mf.eof());
	if (!readMenuData()){
		cout << "menu.dat開檔失敗" << endl;
		return 1;
	}
	sp = pos-1;
	json.open("menu.json", ios::out);
	if (json.fail()){
		cout << "menu.json開檔失敗" << endl;
		return 1;
	}
	json << "[" << endl;
	for (int i=0; i<num; i++){
		dp = 0;
		json << "  {" << endl;
		for (int j=0; j<width; j++){
		  if (buf[sp] != ' '){
			  item[dp] = buf[sp];
			  dp++;
			}
			sp++;
		}
		item[dp] = 0;
		name = convertBig5toUtf8(item, &status);
		json << "    " << '"' << "mainmenu" << '"' << " : ";
		json << '"' << name << '"' << "," << endl;
		json << "    " << '"' << "menuitem" << '"' << " : [" << endl;
		json << "      {" << endl;
		
		json << "      }" << endl;
		json << "    ]" << endl;
		sp = sp + spc - width;
		if (i<(num-1))
		  json << "  }," << endl;
	}
	json << "  }" << endl;
	json << "]" << endl;
	json.close();
	
	return 0;
}

bool readMenuData(){
	fstream fi;
	bool first;
	
	fi.open("menu.dat", ios::in);
	if (!fi)
		return false;
	
	int m=0, d=0, s=0;
	int sp, dp;
	char buf[121];
	char item[121];
	
	do {
		fi.getline(buf, sizeof(buf));
		first = true;
    do {
			if (!first)
		    json << "      }," << endl;
			
      fi.getline(buf, sizeof(buf));			
			if (strlen(buf) == 0)
				break;
      
      sp = 0;
			dp = 0;
			for (int i=0; i<22; i++){
				if (buf[i] = ' ')
					item[dp] = 0;
				else
					item[dp] = buf[sp];
				sp++;
				dp++;
			}
			menuitem[m][d][s] = string(item);
			s++;
			first = false;
			d++;
		} while (!fi.eof());
		m++;
	} while (!fi.eof());
	
	return true;
}