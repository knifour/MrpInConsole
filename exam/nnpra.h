#include <stdint.h>
#include <string.h>
#include <string>

using namespace std;

class PLAYER {
public:
	string name;
	uint32_t score[18];
	uint32_t total;
	float subtol;
	uint8_t rank;
	
	PLAYER();
	void calcTotal(void);
};