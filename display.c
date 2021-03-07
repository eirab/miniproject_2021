/*--------- display.c - Display related functions -------*/
/* Mainly written by Fredrik Lundevall, also containing parts
/* written by Axel Isaksson. 
/* Added to by Eira Birkhammar and Viktor Borg */
  

#include <stdint.h> /* Declarations of uint_32 and the like */
					/* Declarations of system-specific addresses etc */
					/* Declatations for these labs */
#include "pic32mx.h"
#include "assets.h"
#include "display.h"
#include "spaceship.h"
#include "game.h"

/* Declare a helper function which is local to this file */
static void num32asc(char *s, int);

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)

//One frame of the game
uint8_t nextFrame[128 * 4] = {0};

/* Delay function */
void quicksleep(int cyc)
{
	int i;
	for (i = cyc; i > 0; i--)
		;
}
/* Updates frame to be displayed next
Written by Viktor Borg */
void update_frame(int x, int y)
{

	short offset = 0;
	if (y > 0)
	{
		offset = y / 8;
		nextFrame[offset * 128 + x] |= 1 << (y - offset * 8);
	}
}

/* Removes frame 
Written by Viktor Borg */
void remove_frame(int x, int y)
{
	short offset = 0;
	if (y > 0)
	{
		offset = y / 8;
	}
	nextFrame[offset * 128 + x] &= 0 << (y - offset * 8);
}

/* Written by Viktor Borg */
int frame_taken(int x, int y){
    short offset = 0;
    if (y > 0)
    {
        offset = y / 8;
    }
    if((nextFrame[offset * 128 + x] & 1 << (y - offset * 8)) >> (y-offset * 8)){
        return 1;
    }
    else{
        return 0;
    }
}

/* Displays the current frame of the game 
/* Based on pre-existing code, modified by 
Eira Birkhammar and Viktor Borg */
void render_frame()
{
	int i, j;

	insert_spaceship();

	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		//Set page address(offset on y))
		spi_send_recv(0x22);
		spi_send_recv(i);
		//sets offset on x axis
		spi_send_recv(0);
		spi_send_recv(0);

		DISPLAY_CHANGE_TO_DATA_MODE;
		//sends the data to the display.
		for (j = 0; j < 128; j++)
			spi_send_recv(nextFrame[i * 128 + j]);
	}
}

void insert_spaceship()
{
	int page = player.page_pos;
	int i;
	for (i = 0; i < 6; i++)
	{
		nextFrame[(i + (player.xPos) + (page * 128))] = spaceship[i];
	}
}
void delete_frame_data(){
    int i;
    for(i = 0; i <512; i++){
        nextFrame[i] = 0;
    }
}
/* Inserts the monster 
* Written by Eira Birkhammar */
void insert_monster()
{
	int i;

	for (i = 0; i < 8; i++)
	{
		nextFrame[i + 120] = monster[i];
	}
}

void remove_monster(){
    int i;
    for (i = 0; i < 8 ; i++) {
        nextFrame[i + 120] = 0;
    }
}

/********** DISPLAY AND SPI CONFIG FUNCTIONS *********/
/* PRE-EXISTING CODE */
void display_update(void)
{
	int i, j, k;
	int c;
	for (i = 0; i < 4; i++)
	{
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for (j = 0; j < 16; j++)
		{
			c = textbuffer[i][j];
			if (c & 0x80)
				continue;

			for (k = 0; k < 8; k++)
				spi_send_recv(font[c * 8 + k]);
		}
	}
}

/* Helper function, local to this file.
   Converts a number to hexadecimal ASCII digits. */
static void num32asc(char *s, int n)
{
	int i;
	for (i = 28; i >= 0; i -= 4)
		*s++ = "0123456789ABCDEF"[(n >> i) & 15];
}

//Configure SPI for communication with OLED display
void spi_init(void)
{
	/* Set up SPI as master */
	SPI2CON = 0;
	SPI2BRG = 0xF;
	/* SPI2STAT bit SPIROV = 0; */
	SPI2STATCLR = 0x40;
	/* SPI2CON bit CKP = 1; */
	SPI2CONSET = 0x40;
	/* SPI2CON bit MSTEN = 1; */
	SPI2CONSET = 0x20;
	/* SPI2CON bit ON = 1; */
	SPI2CONSET = 0x8000;
}


//Sends data to OLED byte by byte
uint8_t spi_send_recv(uint8_t data)
{
	while (!(SPI2STAT & 0x08))
		;
	SPI2BUF = data;
	while (!(SPI2STAT & 1))
		;
	return SPI2BUF;
}

//Initialise display
void display_init(void)
{
	DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	DISPLAY_ACTIVATE_VDD;
	quicksleep(10000);

	spi_send_recv(0xAE);
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

	spi_send_recv(0x8D);
	spi_send_recv(0x14);

	spi_send_recv(0xD9);
	spi_send_recv(0xF1);

	DISPLAY_ACTIVATE_VBAT;
	quicksleep(100000);

	spi_send_recv(0xA1);
	spi_send_recv(0xC8);

	spi_send_recv(0xDA);
	spi_send_recv(0x20);

	spi_send_recv(0xAF);
}

void display_string(int line, char *s)
{
	int i;
	if (line < 0 || line >= 4)
		return;
	if (!s)
		return;

	for (i = 0; i < 16; i++)
		if (*s)
		{
			textbuffer[line][i] = *s;
			s++;
		}
		else
			textbuffer[line][i] = ' ';
}
