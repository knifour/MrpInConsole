#include <vector>
#include <stdio.h>

using namespace std;

class TEST {
public:
  TEST();
  void printvalue(void);
	
private:	
	vector<int> v;
};

TEST::TEST(){
	v.resize(10, 100);
}

void TEST::printvalue(void){
	for (int i=0; i<v.size(); i++){
		printf("v(%d)=%d\n", i, v[i]);
	}
}

int main(void){
	TEST t;
	
	t.printvalue();
	return 0;
}