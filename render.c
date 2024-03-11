#include <stdio.h>
#include "tilemap.h"
#include "player.h"

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

void render_tilemap(tilemap_t* map){
    int j = 0;
    for(int i = 0; i < map->x_dim * map->y_dim ; i++ ){
        if(i != 0 && i % map->x_dim == 0)
            j++;
        Color tile_color = TileColor(map->tiles[i]);
        DrawRectangle((i % map->x_dim)*TILE_WIDTH,j*TILE_HEIGHT,TILE_WIDTH,TILE_HEIGHT,tile_color);

    }

}

void render_player(player_t* player){

    DrawRectangle(player->pos.x, player->pos.y, player->size.x, player->size.y, WHITE);

}

void DrawScreen(tilemap_t* map , player_t* player, float delta){
        
        ClearBackground(WHITE);
        BeginDrawing();
        render_tilemap(map);
        render_player(player);
        EndDrawing();

}

void update(tilemap_t* map, player_t* player,float delta,uint8_t* update_flag){
    
    if(*update_flag == 1){
        update_player_pos(player,delta);
        DrawScreen(map,player,delta);
        *update_flag = 0;
    }

}




int main(int argc, char** argv){

    tilemap_t* map = init_map(12,16);
    player_t* player = init_player(24/2, 32/2,32,32,400);
    float delta;
    uint8_t should_update = 0;

    InitWindow(TILE_WIDTH*map->x_dim,TILE_HEIGHT*map->y_dim,"SQUARE");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        delta = GetFrameTime();

        DrawScreen(map,player,delta);
        PlayerInput(player,map,delta,&should_update);
        if(should_update == 1)
            update(map,player,delta,&should_update);
    }
}