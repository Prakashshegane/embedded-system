#include <LPC17xx.h>
#include <stdint.h>

void delay(uint32_t ms); // Function declaration

int main()
{
    uint32_t i = 0;
    LPC_GPIO1->FIODIR |= 1<< 27; // Configure P1.19 to P1.26 as output
	LPC_GPIO1->FIOCLR = 1 << 27;
	LPC_GPIO2 ->FIODIR &=~(1<<11);

    while (1)
    {
       if(((LPC_GPIO2 -> FIOPIN)&(1<<11))!=0)
        {
            LPC_GPIO1->FIOSET = 1<<27;// Set the ith bit
            delay(100);
            LPC_GPIO1->FIOCLR = 1<< 27; // Clear the ith bit
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
