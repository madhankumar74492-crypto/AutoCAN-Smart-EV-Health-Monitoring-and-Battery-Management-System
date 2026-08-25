#include"header.h"
 #define LCD_D 0XF<<14
#define RS 1<<10
#define E  1<<11

 void lcd_init(void);
void lcd_data(unsigned char);
void lcd_str(unsigned char*);
void lcd_int(int);
void lcd_float(float);
 void lcd_cmd(unsigned char);
 void lcd_init(void)
{
IODIR0 |=LCD_D|RS|E;
PINSEL0 |=0;
lcd_cmd(0x01);//clear the display
lcd_cmd(0x02);//return the cursor to home position
lcd_cmd(0x0C);//display on ,cursor off 
lcd_cmd(0x28);//8-bit interface made with both lines
}
/////////
void lcd_cmd(unsigned char cmd)
{
IOCLR0=LCD_D;//clear the data pins
IOSET0=(cmd&0xf0)<<10;//assign the cmd byte to data pins of lcd
IOCLR0=RS;// clear rws to selec command register
IOSET0=E;//latch the data to the lcd
delay_ms(2);
IOCLR0=E;//re latch the next byte

IOCLR0=LCD_D;//clear the data pins
IOSET0=(cmd&0x0f)<<14;//assign the cmd byte to data pins of lcd
IOCLR0=RS;// clear rws to selec command register
IOSET0=E;//latch the data to the lcd
delay_ms(2);
IOCLR0=E;//re latch the next byte
}
//////
void lcd_data(unsigned char data)
{
IOCLR0=LCD_D;//clear the data pins
IOSET0=(data&0xf0)<<10;//assign the data to data pins of lcd
IOSET0=RS;//set RS to select the data register
IOSET0=E;// latch the data
delay_ms(2);
IOCLR0=E;//re latch the next byte

IOCLR0=LCD_D;//clear the data pins
IOSET0=(data&0x0f)<<14;//assign the data to data pins of lcd
IOSET0=RS;//set RS to select the data register
IOSET0=E;// latch the data
delay_ms(2);
IOCLR0=E;//re latch the next byte
}
 void lcd_int(int number)

{
 unsigned char arr[100];
 signed char i=0;
 if(number==0)
 lcd_data('0');
 else
{
if(number<0)
{
lcd_data('-');
number=-number;
}
 while(number>0)
{
 arr[i++]=number%10;
 number=number/10;
}
for(--i;i>=0;i--)
lcd_data(arr[i]+48);
}
}
/////////////////////////
void lcd_str(unsigned char *str)
{
while(*str)
{
lcd_data(*str);
str++;
}
}
//////////////////////////////////////////////////////////

