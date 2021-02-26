#include "pic32mx.h"
#include <stdint.h>   
    
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>


void configurePBClock();
void configurePins();
void enable_timer2();
void enableGlobalInterrupts();
void user_isr(void);
void enable_interrupt(void);