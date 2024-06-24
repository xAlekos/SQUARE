#ifndef PLAYER_H
#define PLAYER_H
#include "../utils/utils.h"

typedef enum player_states{

    IDLE,
    MOVING,
    JUMPING,
    SWIMMING

} player_state_t;


typedef struct player{
   
    float speed;
    
    Vector2 vec_speed;

    Vector2 pos;

    Vector2 size;

    player_state_t state;

}player_t;


player_t* init_player(uint16_t starting_x , uint16_t starting_y, uint16_t starting_x_size, uint16_t starting_y_size, float player_speed);

void update_player_pos(player_t* player, float delta);

void PlayerInput(player_t* player ,float delta);

Vector2 player_center_get(player_t* player);

#endif