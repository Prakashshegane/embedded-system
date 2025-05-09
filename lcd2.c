#include <LPC17xx.h>
#include <stdint.h>

#define LCD_DATA_PINS (0xFF << 15)
#define LCD_RS_PIN (1 << 10)
#define LCD_EN_PIN (1 << 11)

void lcd_init(void);
void lcd_cmd_write(char cmd);
void lcd_data_write(char dat);
void lcd_str_write(char *str);
void delay(uint32_t ms);

int main()
{
    char letter = 'A';
    char message[] = "good morning";

    lcd_init();
    lcd_data_write(letter);
    delay(200);
    lcd_cmd_write(0xC0); // Move to second line
    lcd_str_write(message);
    delay(1000);
    lcd_cmd_write(0x01); // Clear display

    return 0;
}

void lcd_cmd_write(char cmd)
{
    LPC_GPIO0->FIOCLR = LCD_DATA_PINS | LCD_RS_PIN | LCD_EN_PIN;
    LPC_GPIO0->FIOSET = (cmd << 15);
    LPC_GPIO0->FIOCLR = LCD_RS_PIN;          // RS = 0 for command
    LPC_GPIO0->FIOSET = LCD_EN_PIN;          // EN = 1
    delay(2);
    LPC_GPIO0->FIOCLR = LCD_EN_PIN;          // EN = 0
}

void lcd_data_write(char dat)
{
    LPC_GPIO0->FIOCLR = LCD_DATA_PINS | LCD_RS_PIN | LCD_EN_PIN;
    LPC_GPIO0->FIOSET = (dat << 15);
    LPC_GPIO0->FIOSET = LCD_RS_PIN;          // RS = 1 for data
    LPC_GPIO0->FIOSET = LCD_EN_PIN;          // EN = 1
    delay(2);
    LPC_GPIO0->FIOCLR = LCD_EN_PIN;          // EN = 0
}

void lcd_str_write(char *str)
{
    while (*str != '\0')
    {
        lcd_data_write(*str);
        str++;
    }
}

void lcd_init(void)
{
    LPC_GPIO0->FIODIR |= LCD_DATA_PINS | LCD_RS_PIN | LCD_EN_PIN; // Set as output
    delay(20); // Wait for LCD power-up
    lcd_cmd_write(0x38); // 8-bit, 2 line, 5x7
    lcd_cmd_write(0x0E); // Display ON, cursor ON
    lcd_cmd_write(0x01); // Clear display
    delay(5);
}

void delay(uint32_t ms)
{
    uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 10000; j++)
        {
            // Simple delay loop
        }
    }
}
