#include  <lpc214x.h>              //Includes LPC2148 register definitions

#define LED1_ON() IO1SET=(1<<16)     //Macro Functions to turn ON LED
#define LED2_ON() IO1SET=(1<<17)
#define LED3_ON() IO1SET=(1<<18)
#define LED4_ON() IO1SET=(1<<19)

#define LED1_OFF() IO1CLR=(1<<16)    //Macro Functions to turn OFF LED
#define LED2_OFF() IO1CLR=(1<<17)
#define LED3_OFF() IO1CLR=(1<<18)
#define LED4_OFF() IO1CLR=(1<<19)

#define LDR (IO1PIN & (1<<24))   //Macro Functions to read LDR status LPC2148 dev. board
       
void Delay(unsigned char j)
{  
    unsigned int  i;
    for(;j>0;j--)
    {
        for(i=0; i<60000; i++);
    }
}      

int  main(void)
{  
    PINSEL0 = 0x00000000;       // Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
   
    IO1DIR = (0<<24);      
    IO1DIR = (1<<19) | (1<<18) | (1<<17) | (1<<16);     // Set P1.16, P1.17, P1.18, P1.19 as Output to control LEDs
   
    while(1)    
    {
        if(LDR == 0) {
            LED1_OFF();
            LED2_OFF();
            LED3_OFF();
            LED4_OFF();
        }
        Delay(100);
        LED1_ON();
        LED2_ON();
        LED3_ON();
        LED4_ON();
    }
}
