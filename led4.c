#include <LPC17xx.h>
#include <stdint.h>

void delay(uint32_t ms); // Function declaration

int main()
{
    uint32_t i = 0;
	uint32_t arr[]={0x81,0x42,0x24,0x18,0x24,0x42,0x81};
    LPC_GPIO1->FIODIR |= 0xFF << 19; // Configure P1.19 to P1.26 as output

    while (1)
    {
        for (i = 0; i <= 7; i++)
        {
            LPC_GPIO1->FIOSET = arr[i] << 19; // Set the ith bit
            delay(100);
            LPC_GPIO1->FIOCLR = arr[i] << 19; // Clear the ith bit
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
