#include "pic32mx.h"
#include <stdint.h>   
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>
#include "controller.h"




  /*
	  This will set the peripheral bus clock to the same frequency
	  as the sysclock. That means 80 MHz, when the microcontroller
	  is running at 80 MHz. Changed 2017, as recommended by Axel.
	*/
void configurePBClock(){

    
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
}

void configurePins(){

	/* Set up output pins */
	AD1PCFG = 0xFFFF;
	ODCE = 0x0;
	TRISECLR = 0xFF;
	PORTE = 0x0;
	
	/* Output pins for display signals */
	PORTF = 0xFFFF;
	PORTG = (1 << 9);
	ODCF = 0x0;
	ODCG = 0x0;
	TRISFCLR = 0x70;
	TRISGCLR = 0x200;
	
	/* Set up input pins */
	TRISDSET = (1 << 8);
	TRISFSET = (1 << 1);
}

void enable_timer2(){
    
 	T2CONSET = 0x70;              //Set prescale to 256, prescale < 256 will generate int requiring more than 16 bits
    PR2 = (80000000 / 256) / 10;  //Set period to 1/10 of a second
    TMR2 = 0;                     //Clear tmr register
    T2CONSET = 0x8000;            // turn timer on
    IEC(0) = IEC(0) | 0x100;    //Set bit 8 to 1 in Interrupt Enable Control Register, T2IE = interrupt enable bit 
    IPC(2) = IPC(2) | 0x1F;    //Set interrupt priorities to highest setting because lecture 6 said so
    
}

void enableGlobalInterrupts(){

    enable_interrupt();       //Call enable interrupt that is in labwork.S
}


/* Interrupt Service Routine */
void user_isr( void ){

  PORTE = PORTE + 1;
  
   
  IFSCLR(0) = 0x100;    // Clear flag
}
