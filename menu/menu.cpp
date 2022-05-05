#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "utf8.h"

using namespace utf8;

bool readMenuData();
void getItem(char*, char*, int, int);
bool isSplit(char);

string menuitem[10][20][3];

int main(int argc, char* argv[]){
	int lin, pos;
	int width, spc, num;
	fstream json;
	
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
		json << "    " << '"' << "mainmenu" << '"' << ":";
		json << '"' << name << '"' << "," << endl;
		json << "    " << '"' << "menuitem" << '"' << ":[" << endl;
		json << "      {" << endl;
		
		for (int j=0; j<20; j++){
			if (menuitem[i][j][0].empty())
				break;
			else{
				if (j>0){
		      json << "      }," << endl;
					json << "      {" << endl;
			  }
		  }
			json << "        " << '"' << "itemname" << '"' << ":";
			json << '"' << menuitem[i][j][0] << '"' << "," << endl;
			json << "        " << '"' << "itemproc" << '"' << ":";
			json << '"' << menuitem[i][j][1] << '"' << "," << endl;
			json << "        " << '"' << "itemdesc" << '"' << ":";
			json << '"' << menuitem[i][j][2] << '"' << endl;
		}
		
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
	int status;
	
	for (int i=0; i<10; i++)
		for (int j=0; j<20; j++)
			for (int k=0; k<3; k++)
				menuitem[i][j][k] = "";
	
	fi.open("menu.dat", ios::in);
	if (!fi)
		return false;
	
	int m=0, d=0;
	char buf[121];
	char item[121];
	
	do {
		fi.getline(buf, sizeof(buf));
    do {
      fi.getline(buf, sizeof(buf));	
			if (strlen(buf) == 1)
				break;
			getItem(buf, item, 1, 22);
			menuitem[m][d][0] = convertBig5toUtf8(item, &status);
			getItem(buf, item, 25, 8);
			menuitem[m][d][1] = convertBig5toUtf8(item, &status);
			getItem(buf, item, 37, 84);
			menuitem[m][d][2] = convertBig5toUtf8(item, &status);
			d++;
		} while (!fi.eof());
		m++;
		d = 0;
	} while (!fi.eof());
	
	return true;
}

void getItem(char* src, char* dst, int strPos, int len){
	int dp = 0;
	for (int i=strPos-1; i<(strPos+len-1); i++){
		if (isSplit(src[i])){
			dst[dp] = 0;
			break;
		} else {
			dst[dp] = src[i];
		}
		dp++;
	}
	
	return;
}

bool isSplit(char c){
	if (c == 0 || c == 10 || c == 13 || c == 32)
		return true;
	else
		return false;
}