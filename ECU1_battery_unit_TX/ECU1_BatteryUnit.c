#include <lpc21xx.h>
#include"header.h"
#include <stdint.h>
#include "delay.h"
#include"can2_txdriver.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BAT_NORMAL    0x00
#define BAT_UNDERVOLT 0x01
#define BAT_OVERTEMP  0x02
#define BAT_FAULT     0x03
int main()
{
    uint32_t temp_adc;
    uint32_t volt_adc;
    uint32_t current_adc;
	float temperature,voltage ;
	char status;
	float MAX_TEMPERATURE=30.0,MIN_VOLTAGE=1.5;
	CAN2_MSG m1;
	CAN2_MSG m2;
	CAN2_MSG m3,m4;
	can2_init();
	PINSEL1 |= 0x01000000;   // P0.28 -> AD0.1 (Temperature)
    PINSEL1 |= 0x04000000;   // P0.29 -> AD0.2 (Current)
    PINSEL1 |= 0x10000000;   // P0.30 -> AD0.3 (Voltage)

	
	while(1)
    {       
                // for temperature------ADC Convertion------
        	ADCR = 0x00200402; //channel 2 selacted ADC operational, 10-bits, 11 clocks for conversion */
		ADCR = ADCR | (1 << 24);
       		while(!(ADDR & 0x80000000));
        	temp_adc = ADDR;
       	 	temp_adc = temp_adc >> 6;// Extract 10-bit ADC result 
        	temp_adc = temp_adc & 0x000003FF;
		temperature = (temp_adc * 3.3f) / 1023.0f;
        	temperature = temperature / 0.01f;
		/*sending data frame*/
	 m1.id=0x101;
	 m1.rtr=0;//data frame
	 m1.dlc=4;
	 m1.byteA=temp_adc;
         m1.byteB=0;
	 can2_tx(m1);
	 delay_ms(200);
		// for voltage------ADC Convertion------
		ADCR = 0x00200408;// channel 4 selected
		ADCR = ADCR | (1<<24); // Start Conversion 
		while ( !(ADDR& 0x80000000) ); // Wait untill done
		volt_adc = ADDR;
		volt_adc = (volt_adc>>6);
		volt_adc= (volt_adc& 0x000003FF);
		voltage = (volt_adc * 3.3f) / 1023.0f;
		////
	 m2.id=0x102;
	 m2.rtr=0;//data frame
	 m2.dlc=4;
	 m2.byteA=volt_adc;
         m2.byteB=0;
	 can2_tx(m2);
	 delay_ms(200);
	    //for current
		ADCR = 0x00200404;// channel 3 selected
		ADCR = ADCR | (1<<24); // Start Conversion 
		while ( !(ADDR& 0x80000000) ); // Wait untill done
	        current_adc = ADDR;
	        current_adc = (current_adc>>6);
 	        current_adc = (current_adc& 0x000003FF);
	 m3.id=0x103;
	 m3.rtr=0;//data frame
	 m3.dlc=4;
	 m3.byteA=current_adc;
         m3.byteB=0;
	 can2_tx(m3);
	 delay_ms(200);
	 ///battery status
	
	if((temp_adc == 0) || (temp_adc >= 1023))
        {
            status = BAT_FAULT;
        }
        else if((volt_adc == 0) || (volt_adc >= 1023))
        {
            status = BAT_FAULT;
        }
        else if(temperature > MAX_TEMPERATURE)
        {
            status = BAT_OVERTEMP;
        }
        else if(voltage < MIN_VOLTAGE)
        {
            status = BAT_UNDERVOLT;
        }
        else
        {
            status = BAT_NORMAL;
        }

					 
	 m4.id=0x104;
	 m4.rtr=0;//data frame
	 m4.dlc=4;
	 m4.byteA=status;
         m4.byteB=0;
	 can2_tx(m4);
	 delay_ms(200);
	}
}


