#include <LPC17xx.h>
#include "llcd.h"

int main() {
  unsigned int adc_value;
  lcd_init();
  LPC_SC->PCONP|=(1<<12);                          //Enable Power to ADC
LPC_SC->PCLKSEL0=(1<<25)|(1<<24);                //Enable Clk to ADC
LPC_PINCON->PINSEL1|=(1<<16);                    //Config P0.24 as AIN1/AD0.2

/*Select Ch2, CLK DIV=4, Burst Mode(cont..), PDN=1(Enable ADC)*/
LPC_ADC->ADCR=(1<<1)|(4<<8)|(1<<16)|(1<<21);

while(1)
{
    while(!((LPC_ADC->ADGDR)&(1<<31)));   // Check Done(EoC) bit Set or not using Polling

    adc_value=(LPC_ADC->ADDR1&(0xFFF<<4));    //Read the Digital Value to any variable

    adc_value=(adc_value)>>4;                 //Right Shift by 4 to get as LSB

    //adc_value=adc_value/13.6;              //Convert Raw temp to Degree Centi garde

    lcd_num(adc_value);                       //Display on LCD

    delay(100);
    lcd_cmd_write(0x01);
}
}