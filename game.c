
/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "pic32mx.h"  /* Declarations of system-specific addresses etc */
#include "display.h"


void *stdin, *stdout, *stderr;




/* Lab-specific initialization goes here */
void labinit( void )
{
   
  
    
    
  return;
}

/* This function is called repetitively from the main program */

void labwork( void ) {
  

  display_update();
  display_string(0, "apa");
  
}