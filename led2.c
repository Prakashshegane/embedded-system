#include<LPC17xx.h>
#include<stdint.h>
void delay(uint32_t ms);   // funcn decln of delay functn
int main()
{
    uint32_t i=0;
    LPC_GPIO1->FIODIR |= 0xFF<<19;            // config
    while(1)
    {
        LPC_GPIO1->FIOSET=0xAA<<19;
        delay(100);
        LPC_GPIO1->FIOCLR=0xAA<<19;
        delay(100);
        LPC_GPIO1->FIOSET=0x55<<19;
        delay(100);
        LPC_GPIO1->FIOCLR=0x55<<19;
        delay(100);
    }
    return 0;
}
void delay(uint32_t ms)
{
	uint32_t i,j;
	for(i=0;i<ms;i++)
{
	for(j=0;j<10000;j++)
	{
	}
}
return ;
}