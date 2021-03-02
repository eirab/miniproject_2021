#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"
#include "assets.h"
#include "spaceship.h"



/* Declare display-related functions from mipslabfunc.c */
void render_frame();
void display_icon();
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void update_frame(int x, int y);
void spi_init(void);
void display_debug( volatile int * const addr );
void remove_frame(int x, int y);
void insert_spaceship();
void insert_monster();
void gen_interval();
uint8_t nextFrame[128*4];