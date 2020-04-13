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
bool searchOld(void);
void searchNew(void);
uint32_t calcValue(uint8_t *para);
void saveTempFile(void);

uint32_t Memory[MAXLEN];
int Count = 0;
uint32_t Target = 0;
char SaveFileName[100];
int Mode;

int main(int argc, char* argv[]){
	FILE *f1;
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
			cout << "遊戲存檔檔名超過99個字元" << endl;
			return 1;
		}
		strcpy(SaveFileName, argv[1]);
	}
	
	Mode = convertMode(argv[2]);
	if (Mode == 0){
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
	  searchNew();	
	} else {
		if (!searchOld()){
			cout << "無法定位到舊紀錄位置，建議清除暫存檔後再重新搜尋" << endl;
			return 3;
		}
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

bool searchOld(void){
	FILE *f1;
	uint8_t buf[4];
	uint32_t *temp;
	int i, cnt, result;
	
	f1 = fopen(SaveFileName, "rb");
	
	temp = new uint32_t[Count];
	
	for (i=0; i<Count; i++)
		temp[i] = Memory[i];
	cnt = Count;
	Count = 0;
	
	for (i=0; i<cnt; i++){
	  result = fseek(f1, temp[i], SEEK_SET);	
		if (result != 0){
			fclose(f1);
			return false;
		}
		if (fread(buf, 1, Mode, f1)!=Mode){
			fclose(f1);
			return false;
		}
		if (calcValue(buf)==Target){
			printf("%u %X\n", temp[i], temp[i]);
			Memory[Count] = temp[i];
			Count++;
		}
	}
	fclose(f1);
	delete [] temp;
	saveTempFile();
	return true;
}

void searchNew(void){
	FILE *f1;
	uint8_t buf[4];
	uint32_t offset = 0, result;
	int i, cnt;
	uint8_t temp;
	
	f1 = fopen(SaveFileName, "rb");
	for (i=0; i<4; i++)
		buf[i] = 0;
	cnt = fread(buf, 1, Mode, f1);
	
	if (cnt != Mode){
		fclose(f1);
		return;
	}
	
	result = calcValue(buf);
	if (result==Target){
		printf("%u %X\n", offset, offset);
		Memory[Count] = offset;
		Count++;
	}
	offset = offset + Mode;
	
	while (fread(&temp, 1, 1, f1) == 1){
		for (i=1; i<Mode; i++)
			buf[i-1] = buf[i];
		buf[Mode-1] = temp;
		result = calcValue(buf);
		if (result == Target){
			if (Count>=MAXLEN){
				cout << "符合條件的資料超過1000筆" << endl;
				break;
			}
			printf("%u %X\n", offset-(Mode-1), offset-(Mode-1));
			Memory[Count] = offset-(Mode-1);
			Count++;
		}
		offset++;
	}
	fclose(f1);
	
	saveTempFile();
}

void saveTempFile(void){
	FILE *f1;
	
	f1 = fopen(FILENAME, "wb");
	for (int i=0; i<Count; i++)
		fwrite(&Memory[i], 1, 4, f1);
	fclose(f1);
}

uint32_t calcValue(uint8_t* para){
	uint32_t temp = 0;
	uint64_t pow = 1;
	
	for (int i=0; i<Mode; i++){
		temp = temp + para[i]*pow;
		pow = pow * 256;
	}
	return temp;
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
  cout << "語法：search {clear|檔名} {BYTE|WORD|DWORD} 數字" << endl  << endl;
	cout << "  clear代表清除暫存檔，無須其他參數" << endl;
	cout << "  檔名代表遊戲存檔的路徑及檔名" << endl << endl;
	cout << "  BYTE, WORD, DWORD代表欲搜尋數字所佔記憶體大小" << endl;
	cout << "  數字代表要搜尋的數字" << endl;
}