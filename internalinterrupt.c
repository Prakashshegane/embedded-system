#include <lpc17xx.h>
#include <stdint.h>
#include "uart.h" // Assuming this header exists

void int_config(void);
void timer_config(void);
void timer_ISR(void) __irq; // Indicate this is an IRQ handler

int main() {
  LPC_GPIO1->FIODIR |= (1 << 19); // Configure P1.19 as output

  uart_config();
  timer_config();
  int_config();

  while (1) {
    LPC_GPIO1->FIOSET |= (1 << 19); // Set P1.19 high
    delay(100);
    LPC_GPIO1->FIOCLR |= (1 << 19); // Clear P1.19 low
    delay(100);
  }
}
void timer_config(void)
{
LPC_SC->PCONP |=(1<<1);
LPC_TIM0->PR=14;
LPC_TIM0->MR0=10000000;
LPC_TIM0->MCR=(1<<0)|(1<<1);
LPC_TIM0->TCR=1<<1;
LPC_TIM0->TCR=1;
uart_str("timer configuare done\r\n");
}
void int_config(void) {
    NVIC_ClearPendingIRQ(TIMER0_IRQn);     // Clear pending interrupts for Timer0
    NVIC_SetPriority(TIMER0_IRQn, 1);      // Set priority for Timer0 interrupt
    NVIC_EnableIRQ(TIMER0_IRQn);           // Enable Timer0 interrupt
    uart_str("Interrupt Config Done\r\n");  
}

void TIMER0_IRQHandler (void) {
    uart_str("Int from Timer\r\n");       // Send a message through UART
    delay(100);
    LPC_TIM0->IR = 1 << 0;                 // Clear interrupt flag
    NVIC_ClearPendingIRQ(TIMER0_IRQn);     // Clear pending interrupt for Timer0
}