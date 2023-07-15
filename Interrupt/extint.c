

#include <lpc214x.h>
#include <stdint.h>

void delay_ms(uint16_t j) /* Function for delay in milliseconds  */
{
    uint16_t x, i;
    for (i = 0; i < j; i++)
    {
        for (x = 0; x < 6000; x++)
            ; /* loop to generate 1 milisecond delay with Pclk=15MHz */
    }
}

__irq void EINT0_ISR(void)
{
    IO0PIN = (IO0PIN ^ 0x00000100); /* Toggle LED */
    delay_ms(5);
    EXTINT = 0x01;
    VICVectAddr = 0x00000000;
}

int main(void)
{
    VPBDIV = 0x00000002;
    EXTMODE = 0x01;                     /* Edge sensitive EINT0 */
    EXTPOLAR = 0x00;                    /* Falling sensitivity for EINT0 */
    EXTINT = 0x01;                      /* Clearing EINT0 flag */
    VICVectAddr0 = (unsigned)EINT0_ISR; /* EINT0 ISR Address */
    VICVectCntl0 = (0x00000020 | 14);   /* Enable EINT0 IRQ slot */
    VICIntEnable = 0x00004000;          /* Enable EINT0 interrupt */
    VICIntSelect = 0x00000000;          /* EINT0 configured as IRQ */
    PINSEL0 = 0x0000000C;               /* Configure P0.1 as EINT0 */
    IO0DIR = 0x00000100;                /* P0.8 as output to LED */
    while (1)
        ;
}
