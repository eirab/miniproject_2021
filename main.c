
#include <stdint.h>   /* Declarations of uint_32 and the like */
 /* Declarations of system-specific addresses etc */
     /* Declatations for these labs */
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>
#include "display.h"
#include "gamestate.h"
#include "game.h"
#include "controller.h"



int main(void) {

    void configurePBClock();
	void configurePins();
	void spi_init();
	void enable_timer2();
	void enableGlobalInterrupts();
	
	
	display_init();
 
	
       
    update_frame(10,27);
    update_frame(10,28);
    update_frame(11,27);
    update_frame(11,28);
    ground_init();

	
	
	labinit(); /* Do any lab-specific initialization */

	while( 1 )
	{
	  labwork(); /* Do lab-specific things again and again */
	}
 
	return 0;
}
