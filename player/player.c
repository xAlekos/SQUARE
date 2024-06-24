#include "player.h"

player_t* init_player(uint16_t starting_x , uint16_t starting_y, uint16_t starting_x_size, uint16_t starting_y_size, float player_speed){
    
    player_t* new_player = (player_t*)calloc(1,sizeof(player_t));
    
    new_player->pos = (Vector2){starting_x, starting_y};
    new_player->size = (Vector2){starting_x_size, starting_y_size};
    new_player->speed = player_speed;

    return new_player;
}

void update_player_pos(player_t* player, float delta){

    player->pos.x += player->vec_speed.x * player->speed * delta;
    player->pos.y += player->vec_speed.y * player->speed * delta;
    player->vec_speed.x = 0;
    player->vec_speed.y = 0;
}


void PlayerInput(player_t* player,world_node_t* map ,float delta){

    if(IsKeyDown(KEY_A)){
        player->vec_speed.x -= 1;
    }

    if(IsKeyDown(KEY_D)){
        player->vec_speed.x += 1;
    }

    if(IsKeyDown(KEY_W)){
        player->vec_speed.y -= 1;
    }

    if(IsKeyDown(KEY_S)){
        player->vec_speed.y += 1;
    }   

}

Vector2 player_center_get(player_t* player){

    Vector2 player_center;
    player_center.x = player->pos.x + player->size.x  / 2;
    player_center.y = player->pos.y + player->size.y / 2;
    return player_center;

}
