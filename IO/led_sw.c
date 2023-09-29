#include  <lpc214x.h>              //Includes LPC2148 register definitions

#define LED1_ON() IO1SET=(1<<16)     //Macro Functions to turn ON LED
#define LED2_ON() IO1SET=(1<<17)
#define LED3_ON() IO1SET=(1<<18)
#define LED4_ON() IO1SET=(1<<19)

#define LED1_OFF() IO1CLR=(1<<16)    //Macro Functions to turn OFF LED
#define LED2_OFF() IO1CLR=(1<<17)
#define LED3_OFF() IO1CLR=(1<<18)
#define LED4_OFF() IO1CLR=(1<<19)

#define SW1 (IO0PIN & 0x00008000)    //Macro Functions to read Push button switches on LPC2148 dev. board
#define SW2 (IO0PIN & 0x00002000)
#define SW3 (IO0PIN & 0x00001000)
#define SW4 (IO0PIN & 0x40000000)                

int  main(void)
{  
    PINSEL0 = 0x00000000;       // Enable GPIO on all pins
    PINSEL1 = 0x00000000;
    PINSEL2 = 0x00000000;
   
    IO0DIR = (0<<12) | (0<<13)  | (0<<15) | (0<<30);        // Set P0.12, P0.13, P0.15, P0.30 as Input to read switch status
    IO1DIR = (1<<19) | (1<<18) | (1<<17) | (1<<16);     // Set P1.16, P1.17, P1.18, P1.19 as Output to control LEDs
   
    while(1)    
    {
    if(!SW1)  {LED1_ON();}         //If switch 1 is pressed turn ON LED1
    else      {LED1_OFF();}        //else turn it OFF  
   
    if(!SW2)  {LED2_ON();}         //If switch 1 is pressed turn ON LED1
    else      {LED2_OFF();}        //else turn it OFF
   
    if(!SW3)   {LED3_ON();}        //If switch 1 is pressed turn ON LED1
    else       {LED3_OFF();}       //else turn it OFF
   
    if(!SW4)   {LED4_ON();}        //If switch 1 is pressed turn ON LED1
    else       {LED4_OFF();}       //else turn it OFF
    }
}
