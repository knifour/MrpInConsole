#ifndef __WIDE_H
#define __WIDE_H

#define SEC0_LOW  ((uint32_t)0x2500)   /* 定義CJK寬字元區段開始 */
#define SEC0_HIGH ((uint32_t)0x257F)  
#define SEC1_LOW  ((uint32_t)0x2E80)  
#define SEC1_HIGH ((uint32_t)0x9FFF)  
#define SEC2_LOW  ((uint32_t)0xAC00)  
#define SEC2_HIGH ((uint32_t)0xD7AF)  
#define SEC3_LOW  ((uint32_t)0xF900)  
#define SEC3_HIGH ((uint32_t)0xFA6D)  
#define SEC4_LOW  ((uint32_t)0xFF01)
#define SEC4_HIGH ((uint32_t)0xFF5E)
#define SEC5_LOW  ((uint32_t)0xFFE0)
#define SEC5_HIGH ((uint32_t)0xFFE6)
#define SEC6_LOW  ((uint32_t)0x1D300)
#define SEC6_HIGH ((uint32_t)0x1D35F)
#define SEC7_LOW  ((uint32_t)0x20000)
#define SEC7_HIGH ((uint32_t)0x2EBEF)
#define SEC8_LOW  ((uint32_t)0x2F800)
#define SEC8_HIGH ((uint32_t)0x2FA1F)  /* 定義CJK寬字元區段結束 */

#endif