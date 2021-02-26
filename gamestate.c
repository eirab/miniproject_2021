#include <stdint.h>   /* Declarations of uint_32 and the like */
 /* Declarations of system-specific addresses etc */
#include "pic32mx.h"
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
    
    return btn;
}

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




int getsw(void){
    
    int switchstatus = (PORTD >> 8) & 0x000F; 
    
    return switchstatus;
}

