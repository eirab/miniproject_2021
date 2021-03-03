
#include <stdlib.h>
void ground_init();
void update_ground();
void send_ground_info();
void load_next_chunk();
void remove_ground_info();
int random_offset(int offset);

extern uint8_t heightmap[192]; // array storing all induviual heights.