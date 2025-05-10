#include <stdio.h>
#include "llcd.h"

int main(void) {
  int result = 0;
  float volts = 0;
  char sVolts[20];
  float temp = 0;
  char sTemp[20];

  LPC_PINCON->PINSEL1 |= (0x01 << 18); // select AD0.2 for P0.25 // DE .no 108
  LPC_SC->PCONP |= (1 << 12);          // Enable ADC clock pg.no 63
  LPC_ADC->ADCR |= (1 << 2) | (3 << 8) | (1 << 21); // from macros

  lcd_init();

 while (1) {
  LPC_ADC->ADCR |= (1 << 24); // Start new Conversion Pg.no

  while (!((LPC_ADC->ADDR2 >> 31) & 0x1)) {
    // Wait until conversion is finished
  }

  result = (LPC_ADC->ADDR2 >> 4) & 0xFFF; // 12 bit Mask to get result
  volts = (result * 3.3) / 4096.0;        // Convert result to Voltage
  sprintf(sVolts, "Voltage:%.2f V", volts);
  lcd_str_write(sVolts);
  lcd_cmd_write(0xC0); // Move cursor to the second line

  temp = volts * 100.0f;
  sprintf(sTemp, "Temp:%.2f C", temp);
  lcd_str_write(sTemp);

  delay(500); // Slowing down Updates to 2 Updates per sec
  lcd_cmd_write(0X01);
}
return ;	
}
