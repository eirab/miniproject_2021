#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"

/* Declare display-related functions from mipslabfunc.c */
void display_image();
void display_init(void);
void display_string(int line, char *s);
void display_update(void);
uint8_t spi_send_recv(uint8_t data);
void update_frame(int x, int y);
void spi_init();
void display_debug( volatile int * const addr );