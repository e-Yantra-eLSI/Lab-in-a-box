#include <lpc214x.h>
#include <stdint.h>
int i = 0;
void delay_ms(uint16_t j)
{
    uint16_t x, i;
    for (i = 0; i < j; i++)
    {
        for (x = 0; x < 6000; x++)
            ; /* loop to generate 1 milisecond delay with Cclk = 60MHz */
    }
}

__irq void PWM_ISR(void)
{
    if (PWMIR & 0x0001)
    {
        PWMIR = 0x0001;
    }

    if (PWMIR & 0x0008)
    {
        PWMIR = 0x0008;
    }

    VICVectAddr = 0x00000000;
}

int main(void)
{

    PINSEL0 = PINSEL0 | 0x00000008;           /* Configure P0.1 as PWM3 */
    VICVectAddr0 = (unsigned)PWM_ISR;         /* PWM ISR Address */
    VICVectCntl0 = (0x00000020 | 8);          /* Enable PWM IRQ slot */
    VICIntEnable = VICIntEnable | 0x00000100; /* Enable PWM interrupt */
    VICIntSelect = VICIntSelect | 0x00000000; /* PWM configured as IRQ */
    PWMTCR = 0x02;                            /* Reset and disable counter for PWM */
    PWMPR = 0x1D;                             /* Prescale Register value */
    PWMMR0 = 20000;                           /* Time period of PWM wave, 20msec */
    PWMMCR = 0x00000203;                      /* Reset and interrupt on MR0 match, interrupt on MR3 match */
    PWMLER = 0x09;                            /* Latch enable for PWM3 and PWM0 */
    PWMPCR = 0x0800;                          /* Enable PWM3 and PWM 0, single edge controlled PWM */
    PWMTCR = 0x09;                            /* Enable PWM and counter */
    while (1)
    {
        for (i = 100; i < 10000; i++)
        {
            PWMMR3 = i; /* For -90 degree position */
            PWMLER = 0x08;
            delay_ms(10);
        }
    }
}