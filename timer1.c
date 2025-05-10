#include<lpc17xx.h>
#define LED_PIN(X) (1<<X)
void timer1_delay_us(unsigned int);
void timer1_init(void);
int main()
{	  
timer1_init();
LPC_GPIO1-> FIODIR |= LED_PIN(24);
timer1_delay_us(2000000);
while(1)
{
if(LPC_TIM1->IR & (1<<0))
{
LPC_GPIO1 -> FIOPIN^=LED_PIN(24);
LPC_TIM1-> IR =1<<0;
}
}
}
void timer1_delay_us(unsigned int us)
{
LPC_TIM1->MR0 = us;
LPC_TIM1->TCR = (1<<0);
}
void timer1_init(void)
{
LPC_SC-> PCONP |=(1<<2);
LPC_SC -> PCLKSEL0 |= (0X01<<4);
LPC_TIM1 -> CTCR = 0x00;
LPC_TIM1->PR =3;
LPC_TIM1->TCR=(1<<1);
LPC_TIM1->MCR |=(1<<1)|(1<<0);
}

