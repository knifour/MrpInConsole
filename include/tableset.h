#ifndef __TABLESET_H
#define __TABLESET_H

#include <stdint.h>

extern uint8_t SHZ[], SVT[], SUL[], SUM[], SUR[], SML[], SMM[], SMR[], SDL[], SDM[], SDR[];
extern uint8_t DHZ[], DVT[], DUL[], DUM[], DUR[], DML[], DMM[], DMR[], DDL[], DDM[], DDR[];
extern uint8_t HZ[],  VT[],  UL[],  UM[],  UR[],  ML[],  MM[],  MR[],  DL[],  DM[],  DR[];

/*uint8_t SHZ[] = "\xe2\x94\x80\x0";
uint8_t SVT[] = "\xe2\x94\x82\x0";
uint8_t SUL[] = "\xe2\x94\x8c\x0";
uint8_t SUM[] = "\xe2\x94\xac\x0";
uint8_t SUR[] = "\xe2\x94\x90\x0";
uint8_t SML[] = "\xe2\x94\x9c\x0";
uint8_t SMM[] = "\xe2\x94\xbc\x0";
uint8_t SMR[] = "\xe2\x94\xa4\x0";
uint8_t SDL[] = "\xe2\x94\x94\x0";
uint8_t SDM[] = "\xe2\x94\xb4\x0";
uint8_t SDR[] = "\xe2\x94\x98\x0";

uint8_t DHZ[] = "\xe2\x95\x90\x0";
uint8_t DVT[] = "\xe2\x95\x91\x0";
uint8_t DUL[] = "\xe2\x95\x94\x0";
uint8_t DUM[] = "\xe2\x95\xa6\x0";
uint8_t DUR[] = "\xe2\x95\x97\x0";
uint8_t DML[] = "\xe2\x95\xa0\x0";
uint8_t DMM[] = "\xe2\x95\xac\x0";
uint8_t DMR[] = "\xe2\x95\xa3\x0";
uint8_t DDL[] = "\xe2\x95\x9a\x0";
uint8_t DDM[] = "\xe2\x95\xa9\x0";
uint8_t DDR[] = "\xe2\x95\x9d\x0";

// 編譯時可以透過-D定義DOUBLELINE使所有的表格代號定義成雙線
// 如果沒有特別定義時，所有的表格代號都是單線
// 定義方法如下：g++ -DDOUBLELINE
#ifdef DOUBLELINE
uint8_t HZ[] = "\xe2\x95\x90\x0";
uint8_t VT[] = "\xe2\x95\x91\x0";
uint8_t UL[] = "\xe2\x95\x94\x0";
uint8_t UM[] = "\xe2\x95\xa6\x0";
uint8_t UR[] = "\xe2\x95\x97\x0";
uint8_t ML[] = "\xe2\x95\xa0\x0";
uint8_t MM[] = "\xe2\x95\xac\x0";
uint8_t MR[] = "\xe2\x95\xa3\x0";
uint8_t DL[] = "\xe2\x95\x9a\x0";
uint8_t DM[] = "\xe2\x95\xa9\x0";
uint8_t DR[] = "\xe2\x95\x9d\x0";
#else
uint8_t HZ[] = "\xe2\x94\x80\x0";
uint8_t VT[] = "\xe2\x94\x82\x0";
uint8_t UL[] = "\xe2\x94\x8c\x0";
uint8_t UM[] = "\xe2\x94\xac\x0";
uint8_t UR[] = "\xe2\x94\x90\x0";
uint8_t ML[] = "\xe2\x94\x9c\x0";
uint8_t MM[] = "\xe2\x94\xbc\x0";
uint8_t MR[] = "\xe2\x94\xa4\x0";
uint8_t DL[] = "\xe2\x94\x94\x0";
uint8_t DM[] = "\xe2\x94\xb4\x0";
uint8_t DR[] = "\xe2\x94\x98\x0";
#endif
*/
#endif