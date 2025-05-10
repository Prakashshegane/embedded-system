#include <LPC17xx.h>

#define LCD_DATA_PINS (0xFF << 15)
#define LCD_RS_PIN(X) (1 << X)
#define LCD_EN_PIN(X) (1 << X)
void lcd_num(unsigned int num);
void lcd_init(void);
void lcd_cmd_write(char);
void lcd_data_write(char);
void lcd_str_write(char *);
void delay(uint32_t );

void lcd_cmd_write(char cmd)
{
LPC_GPIO0 -> FIOCLR = LCD_DATA_PINS;
LPC_GPIO0 -> FIOSET = cmd << 15;
LPC_GPIO0 -> FIOCLR = LCD_RS_PIN(10);   //R.S=0
LPC_GPIO0 -> FIOSET = LCD_EN_PIN(11);  //EN=1
delay(100);
LPC_GPIO0 -> FIOCLR = LCD_EN_PIN(11);    //EN=0
return;
}

void lcd_data_write(char dat)
{
LPC_GPIO0 -> FIOCLR = LCD_DATA_PINS;
LPC_GPIO0 -> FIOSET = dat << 15;
LPC_GPIO0 -> FIOSET = LCD_RS_PIN(10);   //RS=1 ,DATA MODE
LPC_GPIO0 -> FIOSET = LCD_EN_PIN(11);
delay(100);
LPC_GPIO0 -> FIOCLR = LCD_EN_PIN(11);
return;
}

void lcd_str_write(char *str)
{
 while(*str != '\0')
 {
  lcd_data_write(*str);
  str++;
 }
return;
}

void lcd_init(void)
{
LPC_GPIO0 -> FIODIR |= 0xFF << 15;    // p0.15--->P0.22  data pins
LPC_GPIO0 -> FIODIR |= 1<<10;   //R.S.=1 ---->cmd mode   //p0.10
LPC_GPIO0 -> FIODIR |= 1<<11;   // enable=1  //p0.11
lcd_cmd_write(0x38);
lcd_cmd_write(0x0E);
lcd_cmd_write(0x01);
return;
}

void delay(uint32_t ms)
{
uint32_t i,j;
for(i=0;i<ms;i++)
for(j=0;j<6000;j++);
}
void lcd_num(unsigned int num)
{
  if(num)
  {
    lcd_num(num/10);
    lcd_data_write(num%10+0x30);
  }
  }
