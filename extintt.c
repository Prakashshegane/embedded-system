#include <lpc17xx.h>

void External_Int_Config(void);
void delay(unsigned int a);

int main()
{
    LPC_GPIO1->FIODIR |= (0xFF << 19);  // Set P1.19 - P1.26 as output
    External_Int_Config();
    while(1)
    {
        LPC_GPIO1->FIOSET = (1 << 19);  // Turn ON LED at P1.19
        delay(50);
        LPC_GPIO1->FIOCLR = (1 << 19);  // Turn OFF LED at P1.19
        delay(50);
    }
}

void External_Int_Config(void)
{
    LPC_PINCON->PINSEL4 |= (1 << 24);      // Configure P2.12 as EINT2
    LPC_SC->EXTMODE |= (1 << 2);           // Edge sensitive
    LPC_SC->EXTPOLAR |= (1 << 2);          // Rising edge
    NVIC_EnableIRQ(EINT2_IRQn);            // Enable interrupt in NVIC
}

void EINT2_IRQHandler(void)
{
    LPC_GPIO1->FIOSET = (0xF << 21);       // Turn ON LEDs on P1.21 to P1.24
    delay(200);
    LPC_GPIO1->FIOCLR = (0xF << 21);       // Turn OFF LEDs on P1.21 to P1.24
    delay(200);
    LPC_SC->EXTINT = (1 << 2);             // Clear EINT2 interrupt flag
}

void delay(unsigned int a)
{
    unsigned int i, j;
    for(i = 0; i < a; i++)
        for(j = 0; j < 3000; j++);
}
