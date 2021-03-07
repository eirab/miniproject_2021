
/*------- controller.c - functions relating to hardware configuration -------*/
/* Contains functions to configure Timer 2, input/output pins and so on 
/* Based on pre-existing code, added to by Eira Birkhammar and Viktor Borg */


#include <stdint.h>   
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>
#include "controller.h"




/* Set the peripheral bus clock to the same frequency
as the sysclock. That means 80 MHz, when the microcontroller
is running at 80 MHz. Changed 2017, as recommended by Axel.
*/
void configurePBClock(){
    
	/* PRE-EXISTING CODE */
	SYSKEY = 0xAA996655;  /* Unlock OSCCON, step 1 */
	SYSKEY = 0x556699AA;  /* Unlock OSCCON, step 2 */
	while(OSCCON & (1 << 21)); /* Wait until PBDIV ready */
	OSCCONCLR = 0x180000; /* clear PBDIV bit <0,1> */
	while(OSCCON & (1 << 21));  /* Wait until PBDIV ready */
	SYSKEY = 0x0;  /* Lock OSCCON */
}

/* Configures pin values 
PRE-EXISTING CODE */
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
	
	/*Set up LEDS*/
	TRISECLR = 0xFF;
	PORTECLR = 0xFF;
}
/* Configures Timer 2 to generate an interrupt 
every 1/10 of a second 
Authored by Eira Birkhammar */
void enable_timer2(){
    
    T2CONSET = 0x70;              /* Set prescalar to 256 */
    PR2 = (80000000 / 256) / 10;  /* Set period value to cause an interrupt every 1/10 of a second*/
    TMR2 = 0;                     /* Clear TMR2 register  */
    IEC(0) = IEC(0) | 0x100;      /* Enable interrupts */
    IPC(2) = IPC(2) | 0x1F;       /* Set interrupt priority to highest */
    T2CONSET = 0x8000;            /* Turn timer on */
    
}
/* Enables interrupts globally
Written by Eira Birkhammnar */
void enableGlobalInterrupts(){

    enable_interrupt();       //Call enable interrupt that is in gameloop.S
}

/* Disables Timer 2
Written by Viktor Borg */
void disable_timer2(){
    T2CONCLR = 0x8000;
}


