#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */



void gameinit( void );
void gameloop( void );
void user_isr(void);
void gen_interval();
struct Spaceship player;
int interval;
int randomInterval;
