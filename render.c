#include <stdio.h>
#include <string.h>
#include "player.h"


void render_tilemap(tilemap_t* map){
    int j = 0;
    for(int i = 0; i < map->x_dim * map->y_dim ; i++ ){
        if(i != 0 && i % map->x_dim == 0)
            j++;
        Color tile_color = TileColor(map->tiles[i]);
        DrawRectangle((i % map->x_dim)*map->tile_width,j*map->tile_height,map->tile_width,map->tile_height,tile_color);
        DrawText(TextFormat("%d",map->id),50,50,50,MAROON);
    }

}

void render_player(player_t* player){

    DrawRectangle(player->pos.x, player->pos.y, player->size.x, player->size.y, WHITE);

}

void highlight_tile(player_t* player, tilemap_t* map){
    Vector2 tile_pos;
    Vector2 player_center = player_center_get(player);

    tile_pos = tile_cords_from_pos(player_center,map);
    DrawRectangleLines(tile_pos.x * map->tile_width, tile_pos.y * map->tile_height, map->tile_width, map->tile_height, MAROON);

}


void draw_ui(player_t* player, tilemap_t* map){

    Vector2 player_center = player_center_get(player);
    Vector2 tile_pos = tile_cords_from_pos(player_center,map);
    char tile_type[10];
    int tile_cord = tile_pos.y * map->x_dim + tile_pos.x;

    switch (map->tiles[tile_cord].type){
    case WILL:
        strcpy(tile_type,"WILL");
        break;
    case ACID:
        strcpy(tile_type,"ACID");
        break;
    case GROUND:
        strcpy(tile_type,"GROUND");
    default:
        break;
    }
    DrawText(TextFormat("TILE TYPE: %s", tile_type),5,5,25,WHITE);

}

void DrawScreen(world_node_t* map , player_t* player, float delta){
        
        ClearBackground(WHITE);
        BeginDrawing();
        render_tilemap(map->actual);
        render_player(player);
        highlight_tile(player,map->actual);
        draw_ui(player,map->actual);
        EndDrawing();

}

void update(world_node_t** map, player_t* player,float delta,uint8_t* update_flag){
    
    if(*update_flag == 1){
        update_player_pos(player,delta);
        
        if(player->pos.x < 0){
            update_tilemap(WEST,map);
            player->pos.x = TILE_WIDTH * (*map)->actual->x_dim;
        }

        if(player->pos.x > TILE_WIDTH * (*map)->actual->x_dim){
            update_tilemap(EAST,map);
            player->pos.x = 0;
        }

        if(player->pos.y < 0){
            update_tilemap(NORTH,map);
            player->pos.y = TILE_HEIGHT * (*map)->actual->y_dim;
        }

         if(player->pos.y > TILE_HEIGHT * (*map)->actual->y_dim){
            update_tilemap(SOUTH,map);
            player->pos.y = 0;
        }

        DrawScreen(*map,player,delta);
        *update_flag = 0;
    }

}




int main(int argc, char** argv){

    world_node_t* map = init_world_node(0);
    player_t* player = init_player(24/2, 32/2,32,32,400);
    float delta;
    uint8_t should_update = 0;

    InitWindow(map->actual->x_dim * TILE_WIDTH, map->actual->y_dim * TILE_HEIGHT,"SQUARE");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        delta = GetFrameTime();

        DrawScreen(map,player,delta);
        PlayerInput(player,map,delta,&should_update);
        if(should_update == 1)
            update(&map,player,delta,&should_update);
    }
}