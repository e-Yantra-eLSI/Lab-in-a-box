#include  <lpc214x.h>                    //Includes LPC2148 register definitions

#define BUZZER_ON() IO0CLR=(1<<11)       //Macro Functions to turn ON Buzzer
#define BUZZER_OFF() IO0SET=(1<<11)      //Macro Functions to turn OFF Buzzer

void Delay(unsigned int ms);                          

int  main(void)
{  
    PINSEL0 = 0x00000000;       // Enable GPIO on all pins
    PINSEL1 = 0x20000000;
    PINSEL2 = 0x00000000;

    IO0DIR = (1<<11) ;  // Set P0.11 as Output  to control buzzer  
    while(1)    
    {
        BUZZER_ON();
        Delay(100);  
        BUZZER_OFF();
        Delay(100);
    }
}

void Delay(unsigned int ms)
{
    unsigned int i, j;
    for (j = 0; j < (ms / 10); j++)
    {
        for (i = 0; i < 60000; i++)
            ;
    }
}
