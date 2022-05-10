#include <stdint.h>
#include <string.h>
#include <string>

using namespace std;

class PLAYER {
public:
  static int lotter[6];
	static int PAR;
	static void makeLotter(void);
	
	string name;
	uint32_t score[18];
	uint32_t total;
	int hdcp;
	int net;
	
	PLAYER();
	void calcTotal(void);
	bool notLotter(int);
	void calcHDCP(void);
};

int PLAYER::lotter[6] = {0, 0, 0, 0, 0, 0};
int PLAYER::PAR = 71;