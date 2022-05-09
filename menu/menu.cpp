#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "utf8.h"

using namespace utf8;

class MENU{
public:
  int Lin;
	int Pos;
	int Width;
	int Space;
	int Number;
	string FileName;
	string VarString;
	
	string MenuItem[10][20][3];
	
	MENU(){
		Lin = 1; Pos = 1; Width=2; Space=2; Number=1;
		FileName = "menu.json";
		for (int i=0; i<10; i++)
			for (int j=0; j<20; j++)
				for (int k=0; k<3; k++)
					MenuItem[i][j][k] = "";
	}
};

bool writeFormated(MENU&, char*);
bool writeCompacted(MENU&, char*);
bool readMenuData(MENU&);
void getItem(char*, char*, int, int);
bool isSplit(char);

string menuitem[10][20][3];
string outFileName = "menu.scr";

int main(int argc, char* argv[]){
	MENU menu;
	
	if (argc < 6){
		cout << "訊息：參數數量錯誤" << endl;
		cout << "格式：";
		cout << "menu 起始列 起始行 選單字數 選單間隔 選單數量 [檔名]" << endl;
		cout << "  檔名省略時會以格式化方式將轉換結果輸出到menu.json" << endl;
		cout << "  有指定檔名時會將轉換結果輸出到指定的檔名並自動指定副檔名為.js" << endl;
    cout << "  轉換後的檔案開頭會有 const 檔名=\'精簡json格式轉換後的內容\';" << endl;
		cout << "  注意：檔名就是javascript裡面的變數名稱，不可指定副檔名" << endl;
		cout << "        否則在javascript裡面會產生錯誤" << endl;
		return 1;
	} else if (argc > 6) {
		menu.FileName = string(argv[6]) + ".js";
		menu.VarString = "const " + string(argv[6]) + " = \'";
	}
	
	menu.Lin    = atoi(argv[1]);
	menu.Pos    = atoi(argv[2]);
	menu.Width  = atoi(argv[3]);
	menu.Space  = atoi(argv[4]);
	menu.Number = atoi(argv[5]);
	
	char buf[101];
	char item[20];
	int status, sp, dp;
	string name;
	fstream mf;
	
	mf.open("menu.scr", ios::in);
	
	if (!mf.is_open()){
		cout << "開啟menu.scr失敗" << endl;
		return 1;
	}
	
	do {
    for (int i=0; i<(menu.Lin-1); i++){
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
	
	if (!readMenuData(menu)){
		cout << "menu.dat開檔失敗" << endl;
		return 1;
	}
	
	if (argc == 6)
		writeFormated(menu, buf);
	else
		writeCompacted(menu, buf);
	
	return 0;
}

bool writeFormated(MENU& menu, char *buf){
	fstream json;
	char item[20];
	int status, sp, dp;
	string name;
	
	json.open(menu.FileName, ios::out);
	if (json.fail()){
		cout << "輸出檔開檔失敗" << endl;
		return false;
	}
	
	sp = menu.Pos - 1;
	json << "[" << endl;
	for (int i=0; i<menu.Number; i++){
		dp = 0;
		json << "  {" << endl;
		for (int j=0; j<menu.Width; j++){
		  if (buf[sp] != ' '){
			  item[dp] = buf[sp];
			  dp++;
			}
			sp++;
		}
		item[dp] = 0;
		name = convertBig5toUtf8(item, &status);
		json << "    " << '"' << "menuname" << '"' << ":";
		json << '"' << name << '"' << "," << endl;
		json << "    " << '"' << "menuitem" << '"' << ":[" << endl;
		json << "      {" << endl;
		
		for (int j=0; j<20; j++){
			if (menu.MenuItem[i][j][0].empty())
				break;
			else{
				if (j>0){
		      json << "      }," << endl;
					json << "      {" << endl;
			  }
		  }
			json << "        " << '"' << "itemname" << '"' << ":";
			json << '"' << menu.MenuItem[i][j][0] << '"' << "," << endl;
			json << "        " << '"' << "itemproc" << '"' << ":";
			json << '"' << menu.MenuItem[i][j][1] << '"' << "," << endl;
			json << "        " << '"' << "itemdesc" << '"' << ":";
			json << '"' << menu.MenuItem[i][j][2] << '"' << endl;
		}
		
		json << "      }" << endl;
		json << "    ]" << endl;
		sp = sp + menu.Space - menu.Width;
		if (i<(menu.Number-1))
		  json << "  }," << endl;
	}
	json << "  }" << endl;
	json << "]" << endl;
	json.close();
	
	return true;
}

bool writeCompacted(MENU& menu, char* buf){
	fstream json;
	char item[20];
	int status, sp, dp;
	string name;
	
	json.open(menu.FileName, ios::out);
	if (json.fail()){
		cout << "輸出檔開檔失敗" << endl;
		return false;
	}
	
	sp = menu.Pos - 1;
	json << menu.VarString;
	json << "[";
	for (int i=0; i<menu.Number; i++){
		dp = 0;
		json << "{";
		for (int j=0; j<menu.Width; j++){
		  if (buf[sp] != ' '){
			  item[dp] = buf[sp];
			  dp++;
			}
			sp++;
		}
		item[dp] = 0;
		name = convertBig5toUtf8(item, &status);
		json << '"' << "menuname" << '"' << ":";
		json << '"' << name << '"' << ",";
		json << '"' << "menuitem" << '"' << ":[";
		json << "{";
		
		for (int j=0; j<20; j++){
			if (menu.MenuItem[i][j][0].empty())
				break;
			else{
				if (j>0){
		      json << "},";
					json << "{";
			  }
		  }
			json << '"' << "itemname" << '"' << ":";
			json << '"' << menu.MenuItem[i][j][0] << '"' << ",";
			json << '"' << "itemproc" << '"' << ":";
			json << '"' << menu.MenuItem[i][j][1] << '"' << ",";
			json << '"' << "itemdesc" << '"' << ":";
			json << '"' << menu.MenuItem[i][j][2] << '"';
		}
		
		json << "}";
		json << "]";
		sp = sp + menu.Space - menu.Width;
		if (i<(menu.Number-1))
		  json << "},";
	}
	json << "}";
	json << "]";
	json << "\';";
	json.close();
	
	return true;
	return true;
}

bool readMenuData(MENU& menu){
	fstream fi;
	int status;
	
	for (int i=0; i<10; i++)
		for (int j=0; j<20; j++)
			for (int k=0; k<3; k++)
				menu.MenuItem[i][j][k] = "";
	
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
			menu.MenuItem[m][d][0] = convertBig5toUtf8(item, &status);
			getItem(buf, item, 25, 8);
			menu.MenuItem[m][d][1] = convertBig5toUtf8(item, &status);
			getItem(buf, item, 37, 84);
			menu.MenuItem[m][d][2] = convertBig5toUtf8(item, &status);
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