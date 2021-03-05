
#include <stdint.h>
void projectile_init();
void collision_detection_projectile();
void send_projectile_info();
void projectile_update();
void remove_projectile_info();
void activate_projectiles_monster(int count, int x[], int y[]);
void activate_projectile_player(int x, int y);

