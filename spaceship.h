/*--- spaceship.h -----*/
/* Defines the characteristics 
* of the spaceship 

* Author: Eira Birkhammar
*/

#include <stdint.h>
#ifndef SPACESHIP_H
#define SPACESHIP_H

/* xPos - current position of the spaceship
* along the x-axis 
*
* page_pos - current page position, written 
* for an 128x32 OLED where the display is 
* divided into 4 horizontal pages
*
* Refer to the reference manual for the display
* controller: https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
*/
typedef struct Spaceship
{
    int xPos;
    int page_pos;
    
} Spaceship
;


#endif
 https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf
