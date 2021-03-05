#include "pic32mx.h"
#include <stdint.h>   
    
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>


void configurePBClock(void);
void configurePins(void);
void enable_timer2(void);
void enableGlobalInterrupts(void);
void enable_interrupt(void);
void disable_timer2(void);