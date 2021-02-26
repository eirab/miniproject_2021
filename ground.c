#include <stdint.h> 
#include "display.h"
#include "ground.h"
#include <stdlib.h> //library including the rand function.


uint8_t heightmap[128] = {0}; // array storing all induviual heights.
int defaultHeight = 30;//default height of the ground
int indexNewChunk = 0;
void ground_init(){
    int i,j;
    for(i = 4; i<128; i+= 8){
        heightmap[i] = defaultHeight - rand() % 4;//takes the defaul heigh and removes a random number between 0-4.
        for(j = 1; j<=4 ;j++){
           if(defaultHeight - j > heightmap[i]){
               heightmap[i + j] = heightmap[i] + j;
               heightmap[i - j] = heightmap[i] + j;
           }
           else{
               heightmap[i + j] = defaultHeight;
               heightmap[i - j] = defaultHeight;
           }
        }
    }
    send_ground_info(); 
}
//function responsible for sending this data to update_frame.
void send_ground_info(){
    int i,j;
    for(i = 0; i<128; i++){ //goes through all the heights.
        update_frame(i,heightmap[i]);
    }
}

void update_ground(){

    send_ground_info();
}

