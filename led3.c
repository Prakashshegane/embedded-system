#include <LPC17xx.h>
#include <stdint.h>

void delay(uint32_t ms); // Function declaration

int main()
{
    uint32_t i = 0;
    
    LPC_GPIO1->FIODIR |= 0xFF << 19; // Configure P1.19 to P1.26 as output

    while (1)
    {
        for (i = 19; i <= 26; i++)
        {
            LPC_GPIO1->FIOSET = 1 << i; // Set the ith bit
            delay(100);
            LPC_GPIO1->FIOCLR = 1 << i; // Clear the ith bit
            delay(100);
        }
    }

    return 0;
}

void delay(uint32_t ms)
{
    uint32_t i, j;
    for (i = 0; i < ms; i++)
    {
        for (j = 0; j < 10000; j++)
        {
            // Simple delay loop (not accurate, just a rough delay)
        }
    }
	return ;
}
