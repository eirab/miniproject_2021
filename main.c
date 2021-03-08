/*------------ main.c - Main ------------*/
/* Written by Eira Birkhammar and Viktor Borg */

#include <stdint.h>   
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>
#include "display.h"
#include "gamestate.h"
#include "game.h"
#include "controller.h"


int main(void) {

	configurePBClock();
	configurePins();
	spi_init();
	display_init();
	enableGlobalInterrupts();
	
   

	

	gameinit(); /* Initialise game */

    while( 1 )
	{
	  gameloop(); /* Game loop */
	}


	return 0;
}
