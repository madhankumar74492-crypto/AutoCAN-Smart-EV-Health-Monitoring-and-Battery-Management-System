#include <LPC21xx.h>
#include "can2_driver.c"

#define motorpin_1  (1<<0)     // P0.0
#define motorpin_2  (1<<1)     // P0.1

#define HIGH_TEMP       30.0

#define MOTOR_OFF        0x04
#define MOTOR_ON         0x05
void motor_off(void);
void motor_on(void);

int main(void)
{
    CAN2_MSG m1;
    int temp_adc ;
    float temperature;
    unsigned char motor_status;
    PINSEL1 |= 0x01000000;
    IODIR0 |= motorpin_1 | motorpin_2;
    ADCR = 0x00200402;
    can2_init(); 
    while(1)
    {
        can2_rx(&m1);
        ADCR = 0x00200402; //channel 2 selacted ADC operational, 10-bits, 11 clocks for conversion */

	    ADCR = ADCR | (1 << 24);

        while(!(ADDR & 0x80000000));

        temp_adc = ADDR;

        temp_adc = temp_adc >> 6;// Extract 10-bit ADC result 

        temp_adc = temp_adc & 0x000003FF;

		temperature = (temp_adc * 3.3f) / 1023.0f;

        temperature = temperature / 0.01f;
		m1.id =0x105;
        m1.dlc = 2;
        m1.rtr = 0;
        m1.byteA = ((unsigned int)temperature) & 0xFF;
        m1.byteB = ((unsigned int)temperature >> 8) & 0xFF;
        can2_tx(m1);
		if(temperature >= HIGH_TEMP)
		{
    	//Engine is hot
        motor_on();
		motor_status =MOTOR_ON  ;    // Cooling motor ON
		}
		else
		{
        //Engine temperature normal 
        motor_off();// Cooling motor OFF
		motor_status =MOTOR_OFF  ;
        }

        m1.id =0x106;
        m1.dlc = 1;
        m1.rtr = 0;
        m1.byteA = motor_status;
        can2_tx(m1);
}
}
void motor_off(void)
{
    IOCLR0 = motorpin_1;
    IOCLR0 = motorpin_2;
}
void motor_on(void)
{
    IOSET0 = motorpin_1;
    IOCLR0 = motorpin_2;
}
