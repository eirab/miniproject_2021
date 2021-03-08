#include <stdint.h>
#include <stdio.h>

/* Declarations of uint_32 and the like */
                    /* Declarations of system-specific addresses etc */
#include "pic32mx.h"
#include "display.h"
#include <string.h>
#include "gamestate.h"
#include "spaceship.h"
#include <stdbool.h>
#include "game.h"
#include "spaceship.h"
#include "controller.h"
#include "ground.h"
#include "monster.h"
#include "projectile.h"
/* Enables all buttons 
Written by Eira Birkhammar */
void enable_buttons()
{
    //Configure BTN1 to be input
    TRISFSET = 0x2;
    //Clear BTN1 data
    PORTFCLR = 0x2;

    //Configure BTNS 2, 3 and 4 to be inputs
    TRISDSET = 0xE0;
    //Clear data for BTNS 2, 3 and 4
    PORTDCLR = 0xE0;
}

/* Enables switch 1 *7
/* Written by Viktor Borg */
void enable_switch1(){

    TRISDSET = 0x100;
    PORTDCLR = 0x100;
}

int get_switch1(){
    return ((PORTD >> 8) & 0x1);
}
/* Checks if buttons are pressed, in which case the
corresponding bit for the button in question is 1
Written by Eira Birkhammar */
uint32_t get_buttons()
{
    uint32_t btn_d = ((PORTD >> 4) & 0x000E);
    uint32_t btn_f = ((PORTF >> 1) & 0x1);
    uint32_t btn = btn_d | btn_f;

    return btn;
}


/* Polling function to check if any button is pressed 
Written by Eira Birkhammar */
void move()
{

    //for button 1
    if (get_buttons() & 0x1)
    {
        move_up();
    }

    //for button 2
    if (get_buttons() & 0x2)
    {
        move_down();
    }
    //for button 3
    if (get_buttons() & 0x4)
    {
        move_right();
    }

    //for button 4
    if (get_buttons() & 0x8)
    {
        move_left();
    }
}

/* Removes the 6 bytes which represent the spaceship */
/* Written by Eira Birkhammar */
void remove_spaceship()
{

    int page = player.page_pos;
    int curX = (player.xPos + (page * 128));
    int i;

    for (i = curX; i < (curX + 6); i++)
    {
        nextFrame[i] = 0;
    }
}

/* Detects horizontal collision */
/* Written by Eira Birkhammar and Viktor Borg */
void horizontal_collison()
{

    int nextByte = ((player.xPos + (player.page_pos * 128) + 6));
    uint8_t nextData = nextFrame[nextByte];
    if (!(nextData == 0))
    {
        PORTE = PORTE >> 1;
        if(PORTE == 0){
            gameover_routine();
        }
    }
}

/* Moves spaceship left by 3 pixels 
Written by Eira Birkhammar */
void move_left()
{
    int x = (player.xPos + (player.page_pos * 128));
    if (player.xPos > 3)
    {
        remove_spaceship();
        player.xPos = player.xPos - 2;
    }
}

/* Moves spaceship right by 3 pixels 
Written by Eira Birkhammar */
void move_right()
{
    int x = player.xPos;

    if (x < 118)
    {
        remove_spaceship();
        player.xPos = player.xPos + 2;

    }
}
/* Moves spaceship down, unless it's
at the bottom already 
Written by Eira Birkhammar */
void move_down()
{

    if (player.page_pos < 3)
    {
        remove_spaceship();
        player.page_pos = player.page_pos + 1;
    }
}

/* Moves spaceship up one page, unless
the page is 0 (meaning it's already at the top)
Written by Eira Birkhammar */
void move_up()
{

    if (player.page_pos > 0)
    {
        remove_spaceship();
        player.page_pos = player.page_pos - 1;

    }
}
/* the routine for when the game is over. display to the player that the game is over and to play again
 * press btn 1. It also disables timer2 effectily turning game of. then waits untill btn 1 is pressed and
 * then clear screen data and then calls gameinit.
 * Written by Viktor Borg */
void gameover_routine(){

    char string[16];
    sprintf(string,"score: %d",get_score());
    display_string(1,string);
    display_string(0,"GAME OVER!");
    display_string(2,"Press btn 1 to");
    display_string(3,"Play again");
    delete_frame_data();
    display_update();
    disable_timer2();
    remove_projectile_info();
    while(!(get_buttons() & 0x1)){}
    remove_ground_info();
    gameinit();

}







