#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

using namespace std;

#define MAXLEN 1000
#define FILENAME "TempFile"

void prtUsage(void);
int convertMode(char* para);
uint32_t convertValue(char *para);
void saveData(void);

uint32_t Offset = 0;
uint32_t Target = 0;
uint32_t Mode;
char SaveFileName[100];

int main(int argc, char* argv[]){
	FILE *f1;
	uint32_t value;
	char tmp[100];
	int i;

	if (argc != 5){
		cout << "參數數目錯誤" << endl;
		prtUsage();
		return 1;
  }
  
	if ((f1 = fopen(argv[1], "rb")) == NULL){
		cout << "遊戲存檔名不存在，無法繼續" << endl;
		return 2;
	} else {
		fclose(f1);
		if (strlen(argv[1]) > 99){
			cout << "遊戲存檔檔名超過99個字元" << endl;
			return 3;
		}
		strcpy(SaveFileName, argv[1]);
	}
  
  Offset = convertValue(argv[2]);
  
  Mode = convertMode(argv[3]);
  if (Mode == 0){
		cout << "第二參數只能是BYTE或WORD或DWORD" << endl;
		return 1;
	}
	
	Target = convertValue(argv[4]);
  saveData();
  return 0;  
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

void saveData(void){
	FILE *f1;
	
	f1 = fopen(SaveFileName, "rb+");
  if (fseek(f1, Offset, SEEK_SET)==0){
    if (fwrite(&Target, 1, Mode, f1)!=Mode)
      cout << "寫入失敗" << endl;
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
  cout << "語法：modify 檔名 偏移位址 BYTE|WORD|DWORD 數字" << endl  << endl;
	cout << "  檔名代表遊戲存檔的路徑及檔名" << endl << endl;
  cout << "  偏移位址代表要寫入遊戲存檔的位址" << endl;
	cout << "  BYTE, WORD, DWORD代表寫入資料的大小" << endl;
	cout << "  數字代表要寫入的數值" << endl;
}