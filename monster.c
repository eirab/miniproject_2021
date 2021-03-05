#include "monster.h"
#include "display.h"
#include "stdlib.h"
#include "projectile.h"

int iteration = 1;
int hp = 5;
void monster_init(){
    iteration = 1;
    insert_monster();
    hp = 5 * iteration;
}

void monster_collision(){
    int i;
    for(i = 1; i<7 ; i++){
        if(frame_taken(120,i)){
            hp--;
            if(hp == 0){
                iteration++;
                hp = iteration * 5;
                return;
            }
        }
    }
}

void monster_update(){
    monster_collision();
    monster_attack();
}
void monster_attack(){
    int choice = rand() % 2;
    if(choice == 0){
        spawn_basic_attack();
    }
    else if(choice == 1){
        spawn_special_attack();
    }
}

void spawn_basic_attack(){
    int x[5];
    int y[5];
    int i;
    for(i = 0; i<5; i++){
        x[i] = 118 - 2 * i;
        y[i] = 4;
    }
    activate_projectiles_monster(5,x,y);
}

void spawn_special_attack(){
    int x[6];
    int y[6];
    int i;
    for(i = 0 ; i < 3; i++){
        x[i] = 118 - 2*i;
        y[i] = 3;
    }
    for(i = 3; i < 6; i++){
        x[i] = 118 - 2 *(i-3);
        y[i] = 6;
    }
    activate_projectiles_monster(6,x,y);
}


