#include <iostream>
#include <fstream>
#include <iconv.h>
#include <stdio.h>
#include <string.h>
#include "util.h"

using namespace std;

int main(void){
	fstream src("/home/supervisor/mrpdata/BF/BSE/PARCRE.WIN", ifstream::in);
	string buf, dst;
	int status;
	
	while(getline(src, buf)){
		for (int i=0; i<buf.length(); i++){
			if (buf[i] == 13){
				buf.erase(i, 1);
				break;
			}
		}
		dst = convertBig5toUtf8(buf, &status);
		if (status == 0){
			cout << dst << endl;
		} else {
			cout << status << endl;
		}
	}
	
	src.close();
	return 0;
	/*string buf;
	char ibuf[200], obuf[1024];
	char *strsrc, *strdst;
	size_t inbyte, outbyte, ret;
	iconv_t cnv;
	
	cnv = iconv_open("utf8", "big5");
	if (cnv == (iconv_t)-1){
		cout << "open convert error!" << endl;
		return 1;
	}
	
	while(getline(src, buf)){
		for (int i=0; i<buf.length(); i++){
			if (buf[i] == 13){
				buf.erase(i, 1);
				break;
			}
		}
		strcpy(ibuf, buf.c_str());
		strsrc = ibuf;
		strdst = obuf;
		inbyte = strlen(strsrc)+1;
		outbyte = 1024;
		ret = iconv(cnv, &strsrc, &inbyte, &strdst, &outbyte);
		if (ret == -1){
			cout << "convert error!" << endl;
			cout << "in bytes:" << inbyte << endl;
			cout << "reserve bytes:" << outbyte << endl;
			iconv_close(cnv);
			return 1;
		}
		cout << obuf << endl;
	}
	
	iconv_close(cnv);
	src.close();
  return 0;*/
}