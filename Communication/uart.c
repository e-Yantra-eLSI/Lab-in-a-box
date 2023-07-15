#include  <lpc214x.h>		 //Includes LPC2148 register definitions

 
#define Fosc            12000000                    
#define Fcclk           (Fosc * 5)                  
#define Fcco            (Fcclk * 4)                 
#define Fpclk           (Fcclk / 4) * 1             

#define  UART_BPS	9600	 //Set Baud Rate here

const unsigned char SEND_STRING[] = "Nex Robotics PVT LTD\nARM7 LPC214x Development Board\nCommunication Test\nSend any character to continue\n";
const unsigned char SEND_STRING1[] = "Test Passed\n";


void  Delay_Ticks(unsigned int Delay)  //Function to generate finite delay
{  
   unsigned int i;
   for(; Delay>0; Delay--) 
   for(i=0; i<50000; i++);
}


void  Init_UART0(void)					//This function setups UART0
{  
   unsigned int Baud16;
   U0LCR = 0x83;		            // DLAB = 1
   Baud16 = (Fpclk / 16) / UART_BPS;  
   U0DLM = Baud16 / 256;							
   U0DLL = Baud16 % 256;						
   U0LCR = 0x03;
}
				

void  UART0_SendByte(unsigned char data)	   //A function to send a byte on UART0
{  
   U0THR = data;				    
   while( (U0LSR&0x40)==0 );	    
}


void  UART0_SendStr(const unsigned char *str)	 //A function to send a string on UART0
{  
   while(1)
   {  
      if( *str == '\0' ) break;
      UART0_SendByte(*str++);	    
   }
}


int  main(void)
{  
   PINSEL0 = 0x00000005;		    // Enable UART0 Rx and Tx pins
   PINSEL1 = 0x00000000;
   PINSEL2 = 0x00000000;

   Init_UART0();
   UART0_SendStr(SEND_STRING);
   while((U0LSR&0x01)==0);
   UART0_SendStr(SEND_STRING1);
   while(1)	
   {  
     
   }
   return(0);
}