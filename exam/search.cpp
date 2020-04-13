#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

using namespace std;

#define MAXLEN 1000
#define FILENAME "TempFile"

void prtUsage(void);
void clearTempFile(void);
int convertMode(char* para);
int readTempFile(void);
uint32_t convertValue(char *para);
void searchOld(int);
void searchNew(int);

uint32_t Memory[MAXLEN];
uint32_t Count = 0;
uint32_t Target = 0;
char SaveFileName[100];

int main(int argc, char* argv[]){
	FILE *f1;
	int mode;
	uint32_t value;
	char tmp[100];
	int i;

	if (argc <= 1){
		cout << "參數數目錯誤" << endl;
		prtUsage();
		return 1;
	} else if (argc == 2) {
		for (i=0; argv[1][i] != 0; i++){
			if (argv[1][i] >= 97 && argv[1][i] <= 122)
				tmp[i] = (char)(argv[1][i] - 32);
			else
				tmp[i] = (char)argv[1][i];
		}
		tmp[i] = 0;
		if (strcmp(tmp, "CLEAR")!=0){
			cout << "參數數目錯誤" << endl;
			prtUsage();
			return 1;
		} else {
			clearTempFile();
			return 0;
		}
	} else if (argc != 4) {
		cout << "參數數目錯誤" << endl;
		prtUsage();
		return 1;
	}
	
	if ((f1 = fopen(argv[1], "rb")) == NULL){
		cout << "遊戲存檔名不存在，無法繼續" << endl;
		return 1;
	} else {
		fclose(f1);
		if (strlen(argv[1]) > 99){
			cout << "存檔檔名超過99個字元" << endl;
			return 1;
		}
		strcpy(SaveFileName, argv[1]);
	}
	
	mode = convertMode(argv[2]);
	if (mode == 0){
		cout << "第二參數只能是BYTE或WORD或DWORD" << endl;
		return 1;
	}
	
	Target = convertValue(argv[3]);
	
	int result = readTempFile();
	if (result == -1){
		cout << "無法建立暫存檔" << endl;
		return 2;
	}
	
	if (result == 0){
	  searchOld(mode);	
	} else {
		searchNew(mode);
	}
	
	return 0;
}

void clearTempFile(void){
	FILE *f2;
	
	f2 = fopen(FILENAME, "w");
	if (f2 == NULL)
		cout << "無法建立暫存檔" << endl;
	else
	  fclose(f2);
}

int convertMode(char* para){
	char tmp[6];
	int i;
	
	if (strlen(para) > 5)
		return 0;
	
	for (i=0; para[i] != 0; i++){
		if (para[i] >= 97 && para[i] <= 122)
			tmp[i] = (char)(para[i] - 32);
		else
		  tmp[i] = (char)para[i];
	}
	tmp[i] = 0;
	
	if (strcmp(tmp, "BYTE") == 0)
		return 1;
	else if (strcmp(tmp, "WORD") == 0)
	  return 2;
	else if (strcmp(tmp, "DWORD") == 0)
		return 4;
	else
		return 0;
}

int readTempFile(void){
  FILE *f2;
	uint32_t temp;

  f2 = fopen(FILENAME, "rb");	
	if (f2 == NULL){ 
		f2 = fopen(FILENAME, "w");
		if (f2 == NULL)
			return -1;
		else {
			fclose(f2);
			return 0;
		}
	}
	
	while (fread(&temp, 4, 1, f2) == 1){
		Memory[Count] = temp;
		Count++;
	}
	fclose(f2);
	return Count;
}

void searchOld(int mode){
	
}

void searchNew(int mode){
	FILE *f1;
	char buf[4];
	char reg;
	char temp;
	
	f1 = fopen(SaveFileName, "rb");
	reg = 0;
	while (fread(&temp, 1, 1, f1) == 1){
		reg++;
		if (reg == mode){
			
		}
	}
	fclose(f1);
}

uint32_t convertValue(char* para){
	uint32_t value = 0;
	int i = 0;
	
	while (para[i] != 0){
		if (para[i] < '0' || para[i] > '9')
			return 0;
		else
			value = value * 10 + (para[i] - 48);
	  i++;
	}
	return value;
}



void prtUsage(void){
  cout << "語法：search {clean|檔名} {BYTE|WORD|DWORD} 數字" << endl  << endl;
	cout << "  clean代表清除搜尋紀錄，無須其他參數" << endl;
	cout << "  檔名代表存檔的路徑及檔名" << endl << endl;
	cout << "  BYTE, WORD, DWORD代表欲搜尋數字所佔記憶體大小" << endl;
	cout << "  數字代表要搜尋的數字" << endl;
}