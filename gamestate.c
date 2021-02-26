#include <stdint.h>   /* Declarations of uint_32 and the like */
 /* Declarations of system-specific addresses etc */
#include "pic32mx.h"
int getsw(void){
    
    int switchstatus = (PORTD >> 8) & 0x000F; 
    
    return switchstatus;
}

int getbtns(void){
    
    int btn = (PORTD >> 5) & 0x0007; 
    
    return btn; 
    
}
