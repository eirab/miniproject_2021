/* ---------- Monster.c - functions related to the behaviour of the monster --------*/
/* Written by Viktor Borg */


#include "monster.h"
#include "display.h"
#include "stdlib.h"
#include "projectile.h"
#include "gamestate.h"

int iteration = 1;
int hp = 5;
int respawndelay = 0;
int score = 0;
void monster_init(){
    iteration = 1;
    insert_monster();
    hp = 5 * iteration;
    respawndelay = 0;
    score = 0;
}

void monster_collision(){
    int i;
    for(i = 1; i<7 ; i++){
        if(frame_taken(118,i)){
            hp--;
            if(hp == 0){
                iteration++;
                remove_monster();
                score += iteration * 5;
                return;
            }
        }
    }
}

void monster_update(){
    if(hp != 0){
        insert_monster();
        monster_collision();
        monster_attack();
    }
    else{
        respawndelay++;
    }
    if(respawndelay == 10){
        hp = iteration * 5;
        insert_monster();
        respawndelay = 0;
    }
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
        x[i] = 116 - 2 * i;
        y[i] = 4;
    }
    activate_projectiles_monster(5,x,y);
}

void spawn_special_attack(){
    int x[6];
    int y[6];
    int i;
    for(i = 0 ; i < 3; i++){
        x[i] = 116 - 2*i;
        y[i] = 3;
    }
    for(i = 3; i < 6; i++){
        x[i] = 116 - 2 *(i-3);
        y[i] = 6;
    }
    activate_projectiles_monster(6,x,y);
}

int get_score(){
    return score;
}

