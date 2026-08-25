/* main_nodeB_RX.c */
#include "header.h"
#include"can2_driver.c"
#include"4bit.h"
#include <stdio.h>
#define R1  30000.0
#define R2  7500.0
int status;
main(){
    int d;
    float temperature,voltage,current,motor_temperature;
	unsigned char temp[20],volt[20],I[20],m_temp[20];	
	CAN2_MSG m1;
	can2_init();
	lcd_init();
    lcd_init();
    lcd_cmd(0x80);
    lcd_str("  AUTOCAN SMART EV ");
    lcd_cmd(0xC0);
    lcd_str(" HEALTH MONITORING &");
    lcd_cmd(0x94);
    lcd_str(" BATTERY MANAGEMENT ");
    lcd_cmd(0xD4);
    lcd_str(" SYSTEM USING CAN  ");
    delay_ms(3000);
    lcd_cmd(0x01);
    delay_ms(100);
while(1)
	{		
		can2_rx(&m1);
	    if(m1.id==0x101)
		{
		lcd_cmd(0xc0);
		d=m1.byteA;
		temperature= (d* 3.3 / 1023.0)*10;
		temperature= temperature/0.1;
        sprintf(temp,"BTEMP:%d ",(int)temperature);
        lcd_str((unsigned char*)temp);
		}
		if(m1.id==0x102)
		{
		lcd_cmd(0x80);
		d=m1.byteA;
		voltage=(d*3.3/1023.0);
		voltage =voltage * ((R1 + R2) / R2);
        sprintf(volt,"BAT_V:%.1fV",voltage);
        lcd_str((unsigned char*)volt);
		}
		if(m1.id==0x103)
		{
		lcd_cmd(0x8A);
		d=m1.byteA;
		current=(d*3.3/1023.0);
        current = (current -1.65) / 0.100;
		//* ACS712 20A: 2.5V zero-current, 100mV/A 
        sprintf(I,
                    " I=%.1fAMP",
                    current);
        lcd_str(I);
		}
		//baterry status
		if(m1.id==0x104)
        {
        d = m1.byteA;
    	if(d == 0x00){
		lcd_cmd(0xcB);
		lcd_str("         ");
		lcd_cmd(0xcb);
        lcd_str("NORMAL");}
    	else if(d == 0x01){
		lcd_cmd(0xcb);
		lcd_str("         ");
		lcd_cmd(0xcb);
        lcd_str("UNDERVOLT");}
    	else if(d == 0x02){
		lcd_cmd(0xcb);
		lcd_str("         ");
		lcd_cmd(0xcb);
        lcd_str("OVERTEMP");}
    	else if(d == 0x03){
		lcd_cmd(0xcb);
		lcd_str("         ");
		lcd_cmd(0xcb);
        lcd_str("FAULT");}
    	else{
		lcd_cmd(0xcb);
		lcd_str("         ");
		lcd_cmd(0xcb);
        lcd_str("UNKNOWN");}
		}
	if(m1.id == 0x105)
        {
            d = m1.byteA |(m1.byteB << 8);
            motor_temperature = d;
            lcd_cmd(0xD4);
            sprintf(m_temp,"ENGINE_TEMP:%dC",(int)motor_temperature);
            lcd_str(m_temp);
        }
        if(m1.id == 0x106)
        {
        d = m1.byteA;
        lcd_cmd(0x94);
        lcd_str("COOL_MOTOR:");
        lcd_cmd(0x9F);
        if(d == 0x04)
          {
        lcd_str("OFF ");
          }
        else if(d == 0x05)
          {
          lcd_str("ON  ");
          }

        }
        
      }
}


	

