#include <stdint.h> 
#include "display.h"
#include "ground.h"
#include <stdlib.h> //library including the rand function.

#define Default_Height 30
#define MAX_Height_Offset 20



 uint8_t heightmap[160] = {0}; // array storing all induviual heights.
int chunkIndex = 0;
void ground_init(){
    srand(144);
    int i,j;
    for(i = 16; i<160; i+= 32){
        heightmap[i] = Default_Height - rand() % MAX_Height_Offset;//takes the defaul heigh and removes a random number between 0-4.
        for(j = 1; j<=16 ;j++){
           if(Default_Height - j > heightmap[i]){
               heightmap[i + j] = heightmap[i] + j;
               heightmap[i - j] = heightmap[i] + j;
           }
           else{
               heightmap[i + j] = Default_Height;
               heightmap[i - j] = Default_Height;
           }
        }

    }
    send_ground_info(); 
}
//function responsible for sending this data to update_frame.
void send_ground_info(){
    int i,j;
    for(i = 0; i<128; i++){ //goes through all the heights.
        for(j = heightmap[i]; j <= Default_Height; j++){
            update_frame(i,j);
        }
    }
}

void remove_ground_info(){
    int i,j;
    for(i = 0; i<128; i++){ //goes through all the heights.
        for(j = heightmap[i]; j <= Default_Height; j++){
            remove_frame(i,j);
        }

    }
}

void load_next_chunk(){
    heightmap[144] = Default_Height - rand() % MAX_Height_Offset;
    int j;
    for(j = 1; j<=16 ;j++){
        if(Default_Height - j > heightmap[144]){
            heightmap[144 + j] = heightmap[144] + j;
            heightmap[144 - j] = heightmap[144] + j;
        }
        else{
            heightmap[144 + j] = Default_Height;
            heightmap[144 - j] = Default_Height;
        }
    }

}

void update_ground(){
    remove_ground_info();
    int i;
    for(i = 0; i<127; i++){
        heightmap[i] = heightmap[i+1];
    }
    heightmap[127] = heightmap[127 + chunkIndex];
    chunkIndex++;
    if(chunkIndex > 31){
        load_next_chunk();
        chunkIndex = 0;
    }
    send_ground_info();
}




