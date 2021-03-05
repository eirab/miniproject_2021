#include "projectile.h"
#include "display.h"

int xPos[10] = {0};
int yPos[10] = {0};

void projectile_init(){
    int i;
    for(i = 0; i< 9 ; i++){
        xPos[i] = 0;
        yPos[i] = 0;
    }
}
void activate_projectile_player(int x , int y){
    int i;
    for(i = 6 ; i <9 ; i++){
        if(xPos[i] == 0){
            xPos[i] = x;
            yPos[i] = y;
            return;
        }
    }
}
void activate_projectiles_monster(int count,int x[], int y[]){

    if(count > 6){
        count = 6;
    }
    int available = 1;
    int j;
    for(j = 0; j < count ; j++){
        if(xPos[j] != 0){
            available = 0;
        }
    }
    int i;
    if(available){
        for(i = 0; i<count; i++){
            xPos[i] = x[i];
            yPos[i] = y[i];
        }
    }

}

void collision_detection_projectile(){
    int i;
    for(i = 0; i < 9; i++ ){
        if(frame_taken() || xPos[i] <= 0 || xPos[i] >=127){
            xPos[i] = 0;
            yPos[i] = 0;
        }
    }
    send_projectile_info();
}

void projectile_update(){

    remove_projectile_info();
    int i;
    for(i = 0; i<6; i++){
        if(xPos[i] != 0){
            xPos[i] -= 2;
        }

    }
    int j;
    for(j = 6; j < 9 ; j++){
        if(xPos[i] != 0){
            xPos[i] += 2;
        }
    }
    collision_detection_projectile();
}

void send_projectile_info(){

    int i;
    for(i = 0; i<9 ; i++){
        if(xPos[i] != 0){
            update_frame(xPos[i],yPos[i]);
        }
    }
}

void remove_projectile_info(){
    int i;
    for(i = 0; i< 9; i++){
        remove_frame(xPos[i],yPos[i]);
    }
}
