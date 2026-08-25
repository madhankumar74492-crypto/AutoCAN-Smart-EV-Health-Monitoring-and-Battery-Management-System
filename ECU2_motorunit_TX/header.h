/*header.h*/
#ifndef __HEADER_H_
#define __HEADER_H_
#define sw 1<<14

typedef unsigned int u32;
typedef 	signed int s32;
typedef unsigned char u8;
typedef 	signed char s8;
typedef unsigned short int u16;
typedef   signed short int s16;

typedef struct CAN2
{
	u32 id;
	u32 rtr;
	u32 dlc;
	u32 byteA;
	u32 byteB;
}CAN2_MSG;

void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);



#endif


