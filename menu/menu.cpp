#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>
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

bool writeJSON(MENU&, char*, bool);
bool readMenuData(MENU&);
void getItem(char*, char*, int, int);
bool isSplit(char);

int main(int argc, char* argv[]){
	MENU menu;
	
	if (argc < 6){
		cout << "訊息：參數數量錯誤" << endl;
		cout << "格式：";
		cout << "menu 起始列 起始行 選單字數 選單間隔 選單數量 [檔名]" << endl;
		cout << "  檔名省略時會以格式化方式將轉換結果輸出到menu.json" << endl;
		cout << "  有指定檔名時會將轉換結果輸出到指定的檔名並自動指定副檔名為.js" << endl;
    cout << "  轉換後的檔案開頭會有 const json檔名=\'精簡json格式轉換後的內容\';" << endl;
		cout << "  轉換後檔案結尾會有 const obj檔名 = JSON.parse(檔名); 的轉換式" << endl;
		cout << "  注意：json檔名就是javascript裡面的變數名稱，不可指定副檔名" << endl;
		cout << "        否則在javascript裡面會產生錯誤" << endl << endl;
		cout << "轉換時同目錄之下需有以下兩個檔案" << endl;
		cout << "MENU.SCR及MENU.DAT，這兩個檔案都是COBOL程式留下來的檔案" << endl;
		cout << "這兩個檔案的編碼必須是big5編碼" << endl;
		cout << "參數 1~5 必須參考MENU.SCR才能夠設定" << endl;
		cout << "參數值採用big5編碼計算其相關位置，建議使用漢書開啟MENU.SCR及MENU.DAT才不會算錯" << endl;
		cout << "MENU.SCR及MENU.DAT都是從COBOL系統拷貝過來的，請保持大寫的檔名" << endl;
		return 1;
	} else if (argc > 6) {
		string tmp = string(argv[6]) + ".js";
		transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
		menu.FileName = tmp;
		menu.VarString = "json" + string(argv[6]);
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
	
	mf.open("MENU.SCR", ios::in);
	
	if (!mf.is_open()){
		cout << "開啟MENU.SCR失敗" << endl;
		return 1;
	}
	
	do {
    for (int i=0; i<(menu.Lin-1); i++){
			mf.getline(buf, sizeof(buf));
			if (mf.eof()){
				cout << "MENU.SCR不是menu檔" << endl;
				return 1;
			}
		}	
		mf.getline(buf, sizeof(buf));
		mf.close();
		break;
	} while (!mf.eof());
	
	if (!readMenuData(menu)){
		cout << "MENU.DAT開檔失敗" << endl;
		return 1;
	}
	
	if (argc == 6)
		writeJSON(menu, buf, true);
	else
		writeJSON(menu, buf, false);
	
	return 0;
}

bool writeJSON(MENU& menu, char *buf, bool flag){
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
	if (!flag)
		json << "const " << menu.VarString << " = \'";
	(flag) ? json << "[" << endl :
	         json << "[";
	for (int i=0; i<menu.Number; i++){
		dp = 0;
		(flag) ? json << "  {" << endl :
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
		(flag) ? json << "    " << '"' << "menuname" << '"' << ":" :
		         json << '"' << "menuname" << '"' << ":";
		(flag) ? json << '"' << name << '"' << "," << endl :
		         json << '"' << name << '"' << ",";
		(flag) ? json << "    " << '"' << "menuitem" << '"' << ":[" << endl :
		         json << '"' << "menuitem" << '"' << ":[";
		(flag) ? json << "      {" << endl :
		         json << "{";
		
		for (int j=0; j<20; j++){
			if (menu.MenuItem[i][j][0].empty())
				break;
			else{
				if (j>0){
		      (flag) ? json << "      }," << endl :
			             json << "},";
					(flag) ? json << "      {" << endl :
					         json << "{";
			  }
		  }
			(flag) ? json << "        " << '"' << "itemname" << '"' << ":" :
			         json << '"' << "itemname" << '"' << ":";
			(flag) ? json << '"' << menu.MenuItem[i][j][0] << '"' << "," << endl :
			         json << '"' << menu.MenuItem[i][j][0] << '"' << ",";
			(flag) ? json << "        " << '"' << "itemproc" << '"' << ":" :
			         json << '"' << "itemproc" << '"' << ":";
			(flag) ? json << '"' << menu.MenuItem[i][j][1] << '"' << "," << endl :
			         json << '"' << menu.MenuItem[i][j][1] << '"' << ",";
			(flag) ? json << "        " << '"' << "itemdesc" << '"' << ":" :
			         json << '"' << "itemdesc" << '"' << ":";
			(flag) ? json << '"' << menu.MenuItem[i][j][2] << '"' << endl :
			         json << '"' << menu.MenuItem[i][j][2] << '"';
		}
		
		(flag) ? json << "      }" << endl :
		         json << "}";
		(flag) ? json << "    ]" << endl :
		         json << "]";
		sp = sp + menu.Space - menu.Width;
		if (i<(menu.Number-1)){
		  (flag) ? json << "  }," << endl :
			         json << "},";
 	  }
	}
	(flag) ? json << "  }" << endl :
	         json << "}";
	(flag) ? json << "]" << endl :
	         json << "]";
	if (!flag){
		json << "\';" << endl;
	  json << "const obj" << menu.VarString << " = JSON.parse(" << menu.VarString << ");";
	}
	json.close();
	
	return true;
}

bool readMenuData(MENU& menu){
	fstream fi;
	int status;
	
	for (int i=0; i<10; i++)
		for (int j=0; j<20; j++)
			for (int k=0; k<3; k++)
				menu.MenuItem[i][j][k] = "";
	
	fi.open("MENU.DAT", ios::in);
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