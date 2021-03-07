/*------ ground.c - Generates mountains of varying size --------*/
/* Written by Viktor Borg */


#include <stdint.h> 
#include "display.h"
#include "ground.h"
#include <stdlib.h> //library including the rand function.

#define MIN_Height_Offset 10 //minimum height of mountain.
#define Default_Height 30
#define MAX_Height_Offset 20 //maximum height of mountain.



 uint8_t heightmap[192] = {0}; // array storing all induviual heights.
int chunkIndex = 0;
void ground_init(){
    srand(144); //this worlds specific seed.
    int i,j;
    for(i = 32; i<128; i+= 64){
        heightmap[i] = Default_Height - MIN_Height_Offset - random_offset(MAX_Height_Offset - MIN_Height_Offset);//takes the defaul heigh and removes a random number between 0-4.
        for(j = 1; j<=32 ;j++){
           if(Default_Height - j > heightmap[i]){
               heightmap[i + j] = heightmap[i] + j + random_offset(1); //adds random offset of 1 to zero to the height it goes down.
               heightmap[i - j] = heightmap[i] + j + random_offset(1);
           }
           else{
               heightmap[i + j] = Default_Height;
               heightmap[i - j] = Default_Height;
           }
        }

    }
    load_next_chunk();
    send_ground_info(); 
}
//function responsible for sending this data to update_frame.
void send_ground_info(){
    int i,j;
    for(i = 0; i<128; i++){ //goes through all the heights.
        for(j = heightmap[i]; j <= Default_Height; j++){
            update_frame(i,j); //sends the ground data to update_fram and fills in the void between height and ground.
        }
    }
}

void remove_ground_info(){
    int i,j;
    for(i = 0; i<128; i++){ //goes through all the heights.
        for(j = heightmap[i]; j <= Default_Height; j++){
            remove_frame(i,j); //same as send info but it removes info so that we can achieve a scrolling effect.
        }

    }
}
//responsible for loading the next chunk. does same as init but for a single chunk.
void load_next_chunk(){
    heightmap[160] = Default_Height - MIN_Height_Offset - random_offset(MAX_Height_Offset - MIN_Height_Offset);;
    int j;
    for(j = 1; j<=32 ;j++){
        if(Default_Height - j > heightmap[160]){
            heightmap[160 + j] = heightmap[160] + j + random_offset(1);
            heightmap[160 - j] = heightmap[160] + j + random_offset(1);
        }
        else{
            heightmap[160 + j] = Default_Height;
            heightmap[160 - j] = Default_Height;
        }
    }

}
//removes the previous frame then update the ground data and sends it the send info. responsible for checking
// if we need to load a new chunk into the array.
void update_ground(){
    remove_ground_info();
    int i,j;
    for(i = 0; i<127; i++){
        heightmap[i] = heightmap[i+1];
    }
    heightmap[127] = heightmap[127 + chunkIndex];
    chunkIndex++;
    for(j = 0; j<127; j++){
        if(heightmap[j] == Default_Height){
            heightmap[j] = Default_Height - random_offset(5);
        }
    }
    if(chunkIndex > 63){
        load_next_chunk();
        chunkIndex = 0;
    }
    send_ground_info();
}


//helper functions

int random_offset(int offset){
    return rand() % offset;
}

