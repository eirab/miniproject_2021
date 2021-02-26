#include <stdint.h>   /* Declarations of uint_32 and the like */
 /* Declarations of system-specific addresses etc */
#include "pic32mx.h"
#include "display.h"
#include "gamestate.h"
#include <string.h>
struct player foo;

struct player{
    int Lboundx;
    int Rboundx;
    int midX;
    int midY;
    int meshLength;
    int mesh[8];
};

void player_init(){

    foo.meshLength = sizeof(foo.mesh)/sizeof(int);
    foo.Lboundx = 15;
    foo.Rboundx = 16;
    foo.midX = 15;
    foo.midY = 50;
    int temp[] = {50,16,50,15,51,15,51,16};
    memcpy(foo.mesh, temp, sizeof (temp));
}

void player_display(){
    int i;
    for(i = 0; i<foo.meshLength-1  ; i+=2){
        update_frame(foo.mesh[i], foo.mesh[i + 1]);
    }
}

int getsw(void){
    
    int switchstatus = (PORTD >> 8) & 0x000F; 
    
    return switchstatus;
}

int getbtns(void){
    
    int btn = (PORTD >> 5) & 0x0007; 
    
    return btn; 
    
}
