#include <iostream>
#include <stdio.h>
#include <stdint.h>

using namespace std;

#define PARA1 0x535A   /* 長度 1 byte */
#define PARA2 0x534C   /* 長度 1 byte */
#define PARA3 0x5368   /* 長度 1 byte */
#define PARA4 0x4C     /* 長度 3 bytes */
#define PARA5 0x50     /* 長度 3 bytes */
#define PARA6 0x6c     /* 長度 2 bytes */

void prtUsage(void);
int convertMode(char* para);
int convertOffset(char *para);
uint32_t convertValue(char *para);
void processRead(FILE *fp, int offset);
int processWrite(FILE *fp, int offset, uint32_t value);

int main(int argc, char* argv[]){
	FILE *f1;
	int mode;
	int offset;
	uint32_t value;
	
	if (argc < 4) {
		cout << "參數數目錯誤" << endl;
		prtUsage();
	}

	if ((f1 = fopen(argv[1], "rb")) == NULL){
		cout << "檔名不存在，無法繼續" << endl;
		return 1;
	} else {
		fclose(f1);
	}
	
	mode = convertMode(argv[2]);
	if (mode == 0){
		cout << "第二參數只能是r或w" << endl;
		return 1;
	}
	
	offset = convertOffset(argv[3]);
	if (offset == 0){
		cout << "第三參數只能是1~6之間的數字" << endl;
		return 1;
	}
	
  switch (mode){
		case 1:
		  f1 = fopen(argv[1], "rb");
		  processRead(f1, offset);
			break;
		case 2:
		  if (argc != 5){
				cout << "沒有指定要設定的數值" << endl;
				return 1;
			}
			value = convertValue(argv[4]);
			if (value == 0){
				cout << "第四參數只能設定數字，不能有其他符號" << endl;
				return 1;
			}
			f1 = fopen(argv[1], "wb");
			processWrite(f1, offset, value);
			break;
	}	
	
	return 0;
}

int convertMode(char* para){
	if (para[0] == 'r' || para[0] == 'R')
		return 1;
	else if (para[0] == 'w' || para[0] == 'W')
	  return 2;
	else
		return 0;
}

int convertOffset(char* para){
	int result;
	
	result = para[0] - 48;
	if (result < 1 || result > 6)
		return 0;
	else
		return result;
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

void processRead(FILE *fp, int offset){
	char buf[4];
	char ret;
	uint32_t value;
	uint32_t pow;
	
	switch (offset){
		case 1:
		  if (fseek(fp, PARA1, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return;
			}
			ret = fread(buf, 1, 1, fp);
			if (ret = 1){
				value = (uint32_t)buf[0];
				cout << "遙控骰子：" << value << endl;
			}
			fclose(fp);
		  break;
			
		case 2:
		  if (fseek(fp, PARA2, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return;
			}
			ret = fread(buf, 1, 1, fp);
			if (ret = 1){
				value = (uint32_t)buf[0];
				cout << "路障：" << value << endl;
			}
			fclose(fp);
		  break;
			
		case 3:
		  if (fseek(fp, PARA3, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return;
			}
			ret = fread(buf, 1, 1, fp);
			if (ret = 1){
				value = (uint32_t)buf[0];
				cout << "機器娃娃：" << value << endl;
			}
			fclose(fp);
		  break;
			
		case 4:
		  if (fseek(fp, PARA4, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return;
			}
			ret = fread(buf, 3, 3, fp);
			if (ret = 3){
				value = 0;
				for (int i=0, pow=1; i<3; i++){
					value = value + (buf[i]*pow);
					pow = pow * 256;
				}
				cout << "現金：" << value << endl;
			}
			fclose(fp);
		  break;
			
		case 5:
		  if (fseek(fp, PARA5, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return;
			}
			ret = fread(buf, 3, 3, fp);
			if (ret = 3){
				value = 0;
				for (int i=0, pow=1; i<3; i++){
					value = value + (buf[i]*pow);
					pow = pow * 256;
				}
				cout << "存款：" << value << endl;
			}
			fclose(fp);
		  break;
			
		case 6:
		  if (fseek(fp, PARA6, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return;
			}
			ret = fread(buf, 2, 2, fp);
			if (ret = 2){
				value = 0;
				for (int i=0, pow=1; i<2; i++){
					value = value + (buf[i]*pow);
					pow = pow * 256;
				}
				cout << "點券：" << value << endl;
			}
			fclose(fp);
		  break;
	}
	
	return;
}

int processWrite(FILE *fp, int offset, uint32_t value){
	char buf[4];
	char temp;
	uint32_t pow;
	
	for (int i=0; i<4; i++)
		buf[i] = 0;
	
	for (int i=2, pow=65536; i>=0; i--){
		temp = value / pow;
		buf[i] = temp;
		value = value % pow;
		pow = pow / 256;
	}
	
	switch (offset){
		case 1:
			if (fseek(fp, PARA1, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return 1;
			}
			if (value > 255){
				value = 255;
			}
			fwrite(buf, 1, 1, fp);
		  break;
			
		case 2:
		  if (fseek(fp, PARA2, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return 1;
			}
			if (value > 255){
				value = 255;
			}
			fwrite(buf, 1, 1, fp);
		  break;
			
		case 3:
		  if (fseek(fp, PARA3, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return 1;
			}
			if (value > 255){
				value = 255;
			}
			fwrite(buf, 1, 1, fp);
		  break;
			
		case 4:
		  if (fseek(fp, PARA4, SEEK_SET) != 0){
				cout << "錯誤" << endl;
				fclose(fp);
				return 1;
			}
			if (value > 16777215){
				value = 16777215;
			}
			fwrite(buf, 3, 3, fp);
		  break;
			
		case 5:
		  break;
		case 6:
		  break;
	}
	
	fclose(fp);
	return 0;
}

void prtUsage(void){
  cout << "語法：cheat 檔名 r|w 1|2|3|4|5|6 數字" << endl  << endl;
	cout << "  檔名代表存檔的路徑及檔名" << endl << endl;
	cout << "  r代表讀取, w代表寫入" << endl << endl;
	cout << "  1代表遙控骰子" << endl;
	cout << "  2代表路障" << endl;
	cout << "  3代表機器娃娃" << endl;
	cout << "  4代表現金" << endl;
	cout << "  5代表存款" << endl;
	cout << "  6代表點券" << endl << endl;
	cout << "  數字代表你想要把對應的1~6設定成多少值，只有第一參數為w才有意義" << endl;
}