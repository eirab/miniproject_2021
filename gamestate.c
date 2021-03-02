#include <stdint.h>   /* Declarations of uint_32 and the like */
 /* Declarations of system-specific addresses etc */
#include "pic32mx.h"
#include "display.h"
#include <string.h>
#include "gamestate.h"
#include "spaceship.h"
#include <stdbool.h>
#include "game.h"
#include "spaceship.h"
 


void enable_buttons(){


    //Configure BTN1 to be input
    TRISFSET = 0x2;
    //Clear BTN1 data
    PORTFCLR = 0x2;

    //Configure BTNS 2, 3 and 4 to be inputs
    TRISDSET = 0xE0;
    //Clear data for BTNS 2, 3 and 4
    PORTDCLR = 0xE0;
}

uint32_t get_buttons(){

    uint32_t btn_d = ((PORTD >> 4) & 0x000E);
    uint32_t btn_f = ((PORTF >> 1) & 0x1);
    uint32_t btn = btn_d | btn_f;

    return btn;

    
}

void move(){

    //for button 1
    if(get_buttons() & 0x1){
        move_up();
        
    }    
    
     //for button 2
    if(get_buttons() & 0x2){
        move_down();
        
    }
       //for button 3
    if(get_buttons() & 0x4){
        move_right();
    }

       //for button 4
    if(get_buttons() & 0x8){
        move_left();
    }

     
}

void remove_spaceship(){
     
    int page = player.page_pos;
    int curX = (player.xPos + (page *128));
    int i;
  
    for(i = curX; i < (curX+6); i++){
        nextFrame[i] = 0;
    }
}

void horizontal_collison(){

int nextByte = ((player.xPos + (player.page_pos*128)+6));
uint8_t nextData = nextFrame[nextByte];
if(!(nextData == 0)){
    PORTESET = 0xFF;

}



 
}

void move_left(){
int x = (player.xPos + (player.page_pos*128));
if(player.xPos >3){
remove_spaceship();
player.xPos = player.xPos -3;
insert_spaceship();
}
}

void move_right(){
int x = player.xPos;

if(x < 118){

remove_spaceship();
player.xPos = player.xPos+3;
insert_spaceship();
}

}
void move_down(){

    if(player.page_pos < 3){
        remove_spaceship();
        player.page_pos = player.page_pos+1;
        insert_spaceship;
        
    }


}

void move_up(){

    if(player.page_pos > 0){
        remove_spaceship();
        player.page_pos = player.page_pos -1;
        insert_spaceship();


    }


}








