#include <iostream>
#include <stdio.h>

using namespace std;

int main(int argc, char* argv[]){
	FILE *src, *dst;
	int cnt = 0;
	unsigned char buf1[1], buf2[1];
	
  if (argc != 3){
		cout << "Wrong format!" << endl;
		cout << "Usage: comp file1 file2" << endl;
		return 1;
	}
	
	if ((src = fopen(argv[1], "rb")) == NULL){
		cout << "open first file error!" << endl;
		return 1;
	}
	
	if ((dst = fopen(argv[2], "rb")) == NULL){
		cout << "open second file error!" << endl;
		fclose(src);
		return 1;
	}
	
	printf("position  1st  2st\n");
	while (true){
		if (fread(buf1, 1, 1, src) == 0){
			break;
		}
		
		if (fread(buf2, 1, 1, dst) == 0){
			break;
		}
		
		if (buf1[0] != buf2[0]){
			printf("  %04X     %02X   %02X\n", cnt, buf1[0], buf2[0]);
		}
		
		cnt++;
	}
	
	
	cout << "total byte: " << cnt << endl;
	fclose(dst);
	fclose(src);
	return 0;
}