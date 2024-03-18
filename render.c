#include <stdio.h>
#include "player.h"


void render_tilemap(tilemap_t* map){
    int j = 0;
    for(int i = 0; i < map->x_dim * map->y_dim ; i++ ){
        if(i != 0 && i % map->x_dim == 0)
            j++;
        Color tile_color = TileColor(map->tiles[i]);
        DrawRectangle((i % map->x_dim)*map->tile_width,j*map->tile_height,map->tile_width,map->tile_height,tile_color);

    }

}

void render_player(player_t* player){

    DrawRectangle(player->pos.x, player->pos.y, player->size.x, player->size.y, WHITE);

}

void highlight_tile(player_t* player, tilemap_t* map){
    Vector2 tile_pos;
    Vector2 player_center;
    player_center.x = player->pos.x + map->tile_width  / 2;
    player_center.y = player->pos.y + map->tile_height / 2;
    tile_pos = get_tile(player_center,map);
    DrawRectangleLines(tile_pos.x * map->tile_width, tile_pos.y * map->tile_height, map->tile_width, map->tile_height, MAROON);

}

void DrawScreen(tilemap_t* map , player_t* player, float delta){
        
        ClearBackground(WHITE);
        BeginDrawing();
        render_tilemap(map);
        render_player(player);
        highlight_tile(player,map);
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

    InitWindow(map->tile_width*map->x_dim,map->tile_height*map->y_dim,"SQUARE");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        delta = GetFrameTime();

        DrawScreen(map,player,delta);
        PlayerInput(player,map,delta,&should_update);
        if(should_update == 1)
            update(map,player,delta,&should_update);
    }
}