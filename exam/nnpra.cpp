#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "nnpra.h"

int MAX[] = {7, 9, 9, 5, 7, 7, 5, 7, 5, 9, 5, 7, 5, 7, 5, 9, 7, 9};

void makeLotter(void);
int myRandom(int, int);

int main(void){
	fstream game;
	string buf;
	char format[20];
	int cnt = 0;
	int col = 0;
	int p = 0;
	
	game.open("kf12.txt", ios::in);
	if (!game)
	  return 1;
		
	while (getline(game, buf))
	  cnt++;
	game.close();
		
	PLAYER mon[cnt];
	PLAYER* pt[cnt];
	PLAYER* swap;
	char temp[20];
	cnt = 0;
	col = 0;
	game.open("kf12.txt", ios::in);
	while (getline(game, buf)){
		col = 0;
		p = 0;
		for (int i=0; buf[i]!=0; i++){
			if (buf[i]==','){
				if (col==0){
					temp[p] = 0;
					mon[cnt].name.assign(temp);
					col++;
					p=0;
					continue;
				} else if (col>=1 && col<=18) {
					temp[p] = 0;
					mon[cnt].score[col-1] = stoi(temp, nullptr);
					col++;
					p=0;
					continue;
				} else {
					cout << "error!" << endl;
					continue;
				}
			}
			temp[p] = buf[i];
			p++;
		}
		if (col==18){
			temp[p] = 0;
			mon[cnt].score[col-1] = stoi(temp, nullptr);
		}
		cnt++;
	}
	
	PLAYER::makeLotter();
	
	for (int i=0; i<cnt; i++)
	  mon[i].calcHDCP();

  for (int i=0; i<cnt; i++)
    pt[i] = &mon[i];	
		
	for (int i=0; i<cnt-1; i++){
		for (int j=i+1; j<cnt; j++){
			if (pt[i]->net > pt[j]->net){
				swap = pt[i];
				pt[i] = pt[j];
				pt[j] = swap;
			}
		}
	}
	
	cout << "新新貝利亞";
	cout << "#" << PLAYER::lotter[0]+1;
	for (int i=1; i<6; i++)
	  cout << ",#" << PLAYER::lotter[i]+1;
	cout << endl;
	cout << "姓  名  總桿  差點  淨桿" << endl;
	cout << "========================" << endl;
	for (int i=0; i<cnt; i++){
		cout << pt[i]->name;
		sprintf(format, "%4d  %4d  %4d", pt[i]->total, pt[i]->hdcp, pt[i]->net);
		cout << "  " << format << endl;
	}
	
	return 0;
}

int myRandom(int min, int max){
	return ( rand() % (max - min + 1) + min );
}

PLAYER::PLAYER(){
	name = "";
	for (int i=0; i<18; i++)
	  score[i] = 0;
	total = 0;
	hdcp = 0;
	net = 0;
}

void PLAYER::calcTotal(void){
	total = 0;
	for (int i=0; i<18; i++)
	  total = total + score[i];
}

void PLAYER::makeLotter(void){
	int norep[18];
	int temp;
	
	for (int i=0; i<18; i++)
	  norep[i] = 0;
		
	srand(time(NULL));
	
	for (int i=0; i<6; i++){
		do {
			temp = myRandom(0, 17);
		} while (norep[temp] == 1);
		norep[temp] = 1;
		lotter[i] = temp;
	}
}

bool PLAYER::notLotter(int hole){
	for (int i=0; i<6; i++)
	  if (lotter[i] == hole)
		  return false;
	
	return true;
}

void PLAYER::calcHDCP(void){
	double tol = 0.0;
	double temp;
	
	calcTotal();
	
	for (int i=0; i<18; i++){
		if (notLotter(i)){
			if (score[i] > MAX[i])
			  tol = tol + MAX[i];
			else
			  tol = tol + score[i];
		}
	}
	temp = (tol * 1.5) - PAR;
	temp = round(temp * 0.8);
	
	if (temp < 0)
	  temp = 0;
	
	hdcp = (int)temp;
	net = total - hdcp;
}