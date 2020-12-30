#include <iostream>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "nnpra.h"

int max[] = {7, 9, 9, 5, 7, 7, 5, 7, 5, 9, 5, 7, 5, 7, 5, 9, 7, 9};
int lotter[6];

void makeLotter(void);
int myRandom(int, int);

int main(void){
	fstream game;
	string buf;
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
	
	makeLotter();
	
	for (int i=0; i<cnt; i++)
	  mon[i].calcTotal();
	
	for (int i=0; i<cnt; i++){
		cout << mon[i].name;
		for (int j=0; j<18; j++)
		  cout << "," << mon[i].score[j];
		cout << " = " << mon[i].total << endl;
	}
	
	for (int i=0; i<6; i++)
	  cout << lotter[i] << " ";
	cout << endl;
	
	return 0;
}

int myRandom(int min, int max){
	return ( rand() % (max - min + 1) + min );
}

void makeLotter(void){
	int norep[18];
	int temp;
	
	for (int i=0; i<18; i++)
	  norep[i] = 0;
	
	srand(time(NULL));
	
	for (int i=0; i<6; i++){
    do {
			temp = myRandom(0, 17);
			cout << temp << ",";
		}	while(norep[temp] == 1);	
		norep[temp] = 1;
		lotter[i] = temp;
	} 
}

PLAYER::PLAYER(){
	name = "";
	for (int i=0; i<18; i++)
	  score[i] = 0;
	total = 0;
	subtol = 0;
	rank = 0;
}

void PLAYER::calcTotal(void){
	for (int i=0; i<18; i++)
	  total = total + score[i];
}