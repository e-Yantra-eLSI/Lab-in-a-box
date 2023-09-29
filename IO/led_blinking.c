#include  <lpc214x.h>              //Includes LPC2148 register definitions

#define LED1_ON() IO1SET=(1<<16)     //Macro Functions to turn ON LED
#define LED1_OFF() IO1CLR=(1<<16)    //Macro Functions to turn OFF LED
void Delay(unsigned int);

int  main(void)
{  
    PINSEL2 = 0x00000000;       // Enable GPIO on all pins
    IO1DIR = (1<<16);           // Set P1.16 as Output  to control LEDs
    while(1)    
    {
        LED1_ON();
        Delay(100);
        LED1_OFF();
        Delay(100);
    }
}

void Delay (unsigned int ms)
{
    unsigned int i, j;
    for (j = 0; j < (ms / 10); j++)
    {
        for (i = 0; i < 60000; i++);
    }
}
