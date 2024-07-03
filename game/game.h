#ifndef GAME_H
#define GAME_H

#include "../render/render.h"

enum game_state{
    NORMAL,
    DIALOGUE,
    PAUSE
};

typedef struct game_ctx{


    
}game_ctx;

void update(world_node_t** map, player_t* player,float delta);

void dialog_event(world_node_t* map , player_t* player, float delta);

#endif