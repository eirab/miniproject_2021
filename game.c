/*************************************
 * game.c contains the gameloop, where the function
 * gameloop() is repeatedly called from main.c. 
 * 
 * Last updated: 2021-03-03
 * 
 * Written by: Eira Birkhammar & Viktor Borg


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */
#include "display.h"
#include "gamestate.h"
#include "assets.h"
#include "game.h"
#include "ground.h"
#include "spaceship.h"


struct Spaceship player;
int interval;
int randomInterval;

void *stdin, *stdout, *stderr;

/* Interrupt Service Routine */
void user_isr( void ){
   
    move();
    update_ground();
    render_frame();
   

    IFSCLR(0) = 0x100;    // Clear flag
}
/* Doesn't work, is supposed to generate a
random interval where monsters appear */
void gen_interval(){

    int p = rand()%((10000)-100) + 100;
   randomInterval = p;

}


/* Initialises the game and sets start-up values*/
void gameinit( void )
{
   randomInterval = 0;
   interval = 0;
   gen_interval();
   ground_init();
   enable_buttons();
   //Bit 0, first byte
   player.xPos = 0;
   player.page_pos = 0;

  return;
}

/* Called repeatedly from main */
void gameloop( void ) {

   interval++;
  // int randomMonster = rand()%((2+1)-1) + 1;
   
   horizontal_collison();
   PORTECLR = 0xFF;

   if(interval == randomInterval){
      insert_monster();
      interval = 0;
      gen_interval();
   }

   

  
}