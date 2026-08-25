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



void delay_sec(u32 sec);
//void delay_ms(u32 ms);
void delay_ms(unsigned int ms);
void gpio_direction_input(u32 port,u32 pin);
void gpio_direction_output(u32 port,u32 pin);
u32 gpio_get_value(u32 port,u32 pin);
void gpio_set_value(u32,u32,u32);


unsigned char uart0_rx(void);
void uart0_tx(unsigned char data);
void uart0_init(unsigned int baud);
void uart0_tx_string(char *ptr);
void uart0_tx_integer(int num);
void uart0_tx_float(float num);
void uart0_tx_hex(int num);










void can2_init(void);
void can2_tx(CAN2_MSG m1);
void can2_rx(CAN2_MSG *m1);



#endif


