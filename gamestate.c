#include <stdint.h>   /* Declarations of uint_32 and the like */
 /* Declarations of system-specific addresses etc */
#include "pic32mx.h"
#include "display.h"
#include <string.h>
#include "gamestate.h"



void enable_buttons(){


    //Configure BTN1 to be input
    TRISFSET = 0x2;
    //Clear BTN1 data
    PORTFCLR = 0x2;

    //Configure BTNS 2, 3 and 4 to be inputs
    TRISESET = 0xE0;
    //Clear data for BTNS 2, 3 and 4
    PORTECLR = 0xE0;
}

int get_buttons(){

    int btn = ((PORTD >> 4) & 0x00E) | ((PORTF >> 1) & 0x30); 
}


struct Player{

    int Lboundx;
    int Rboundx;
    int midX;
    int midY;
    int meshLength;
    int mesh[8];
} Player;

 /*Player player_init(){

    
    foo.meshLength = sizeof(foo.mesh)/sizeof(int);
    foo.Lboundx = 15;
    foo.Rboundx = 16;
    foo.midX = 15;
    foo.midY = 50;
    int temp[] = {50,16,50,15,51,15,51,16};
    memcpy(foo.mesh, temp, sizeof (temp));
    return foo;
}*/

/*void player_display(){
    int i;
    for(i = 0; i<foo.meshLength-1  ; i+=2){
        update_frame(foo.mesh[i], foo.mesh[i + 1]);
    }
}*/


void move(){

    //for button 1
    if(get_buttons() & 0x1){
        PORTEINV = 0x1;
    }
    
     //for button 2
    if(get_buttons() & 0x2){
        PORTEINV = 0x2;
    }
       //for button 3
    if(get_buttons() & 0x4){
        PORTEINV = 0x3;
    }

       //for button 4
    if(get_buttons() & 0x8){
        PORTEINV = 0x4;
    }

    
}


