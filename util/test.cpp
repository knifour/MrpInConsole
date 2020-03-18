#include <stdio.h>
#include <iostream>
#include <string>
#include <screen.h>
#include <util.h>

using namespace std;

int main(void){
	int** data;
	
	data = NEW2D(5, 5, int);
	
	for (int i=0; i<5; i++)
		for (int j=0; j<5; j++)
			data[i][j] = i*j;
		
	for (int i=0; i<5; i++){
		for (int j=0; j<5; j++)
			cout << data[i][j] << " ";
	  cout << endl;
	}
  
	delete [] data;
	return 0;
}