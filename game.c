/*------- game.c - Game loop file ---------*/
 /* game.c contains the gameloop, where the function
 * gameloop() is repeatedly called from main.c. 
 * 
 *
 * 
 * Written by: Eira Birkhammar & Viktor Borg */


#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */
#include "display.h"
#include "gamestate.h"
#include "assets.h"
#include "game.h"
#include "ground.h"
#include "spaceship.h"
#include "projectile.h"
#include "monster.h"


struct Spaceship player;
int interval;
int randomInterval;

void *stdin, *stdout, *stderr;

/* Interrupt service routine for Timer 2 */
void user_isr( void ){
   
    move(); /* Poll buttons */
    if(get_switch1()){
//<<<<<<< Updated upstream
        //activate_projectile_player(player.xPos + 7,player.page_pos * 8 + 4); /* Poll switch status */
//=======
        activate_projectile_player(player.xPos + 8,player.page_pos * 8 + 4);
//>>>>>>> Stashed changes
    }
    monster_update(); /* Update monster */
    update_ground(); /* Update ground*/
    projectile_update(); /* Update projectile*/
    horizontal_collison(); /* Is there a horizontal collison? */

    render_frame(); /* Display updated frame */

    IFSCLR(0) = 0x100;    /* Clear Timer 2 flag */
}
/* Doesn't work, is supposed to generate a
random interval where monsters appear */
void gen_interval(){

    int p = rand()%((10000)-100) + 100;
   randomInterval = p;

}


/* Initialises the game and sets start-up values*/
void gameinit( void ){  
   
   /* Enable Timer 2 */
   enable_timer2();
    
   randomInterval = 0;
   interval = 0;
   gen_interval();
  
   /* Enable buttons and switch 1 */
    enable_buttons();
    enable_switch1();
   
   /* Initialise spaceship positon */
    player.xPos = 0;
    player.page_pos = 0;
    PORTESET = 0x1F;
   
   /* Initialise frame elements */
    ground_init();
    projectile_init();
    monster_init();

  return;
}

/* Called repeatedly from main */
void gameloop( void ) {

   interval++;
  // int randomMonster = rand()%((2+1)-1) + 1;


   if(interval == randomInterval){
      //insert_monster();
      interval = 0;
      gen_interval();
   }

   

  
}
