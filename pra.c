#include<LPC17xx.h>
#include<stdint.h>
void delay(uint32_t ms);
int main()
{
	LPC_GPIO1 ->  FIODIR  |=1<<19;
	while(1)
	{
		LPC_GPIO1 -> FIOSET |=1<<19;
		delay(100);
		LPC_GPIO1 -> FIOCLR = 1<<19;
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