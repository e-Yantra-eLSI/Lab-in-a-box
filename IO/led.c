#include <lpc214x.h> //Includes LPC2148 register definitions

#define LED1_ON() IO1SET = (1 << 16) // Macro Functions to turn ON LED
#define LED2_ON() IO1SET = (1 << 17)
#define LED3_ON() IO1SET = (1 << 18)
#define LED4_ON() IO1SET = (1 << 19)

#define LED1_OFF() IO1CLR = (1 << 16) // Macro Functions to turn OFF LED
#define LED2_OFF() IO1CLR = (1 << 17)
#define LED3_OFF() IO1CLR = (1 << 18)
#define LED4_OFF() IO1CLR = (1 << 19)

int main(void)
{
    PINSEL0 = 0x00000000; // Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;

    IO1DIR = (1 << 19) | (1 << 18) | (1 << 17) | (1 << 16); // Set P1.16, P1.17, P1.18, P1.19 as Output	to control LEDs

    while (1)
    {
        LED1_ON();
        Delay(500);
        LED1_OFF();
        Delay(500);
    }
}
void Delay(unsigned int ms) // delay routine
{
    unsigned int i, j;
    for (j = 0; j < (ms / 10); j++)
    {
        for (i = 0; i < 60000; i++)
            ;
    }
}