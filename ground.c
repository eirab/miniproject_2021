#include <stdint.h> 
#include "mipslab.h"
#include "ground.h"
#include <stdlib.h> //library including the rand function.

uint8_t heightmap[128] = {0}; // array storing all induviual heights.
int defaultHeight = 31;//default height of the ground

void ground_init(){
    int i;
    for(i = 0; i<128; i++){
        heightmap[i] = defaultHeight - rand() % 4;//takes the defaul heigh and removes a random number between 0-4.
    }
    send_ground_info(); 
}
//function responsible for sending this data to update_frame.
void send_ground_info(){
    int i,j;
    for(i = 0; i<128; i++){ //goes through all the heights.
        for(j = 31; j >= (31 - heightmap[i]); j--)//fills all the heights so we dont draw one pixel.
        {
            update_frame(i,heightmap[i] + (31-heightmap[i]));
        }
    }
}

void update_ground(){
    uint8_t newGround = defaultHeight - rand() % 4;
    int i;
    for(i = 0; i < 128 ; i++){
        if(i != 127){
            heightmap[i] = heightmap[i+1];
        }
        else{
            heightmap[i] = newGround;
        }
    }
    send_ground_info();
}

