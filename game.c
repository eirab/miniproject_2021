
/* mipsgameloop.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */
#include "display.h"
#include "gamestate.h"
#include "assets.h"
#include "game.h"
#include "ground.h"
#include "spaceship.h"



#define PAGE0_MIN_X 0
#define PAGE0_MAX_X 122
#define PAGE1_MIN_X 128
#define PAGE1_MAX_X 249
#define PAGE2_MIN_X 256
#define PAGE2_MAX_X 377
#define PAGE3_MIN_X 384
#define PAGE3_MAX_X 506

#define SPACESHIP_ARR_LEN 6


  uint8_t sp[6]= {195,
195,
126,
126,
126,
60};

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

void gen_interval(){


    int p = rand()%((10000)-100) + 100;
   randomInterval = p;

}



/* Lab-specific initialization goes here */
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

/* This function is called repetitively from the main program */

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