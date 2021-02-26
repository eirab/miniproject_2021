#include "pic32mx.h"
#include <stdint.h>   
    
#include "ground.h"
#include "pic32mx.h"
#include <stdlib.h>


void configurePBClock();
void configurePins();
void enable_timer2();
void enable_interrupt();
void usr_isr(void);