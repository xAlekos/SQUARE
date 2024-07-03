#include "../render/render.h"

void update(world_node_t** map, player_t* player,float delta){
    
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


}


void dialog_event(world_node_t* map , player_t* player, float delta){

    dialog_t* dial = malloc(sizeof(dialog_t));
    read_dialog(dial,"./misc/dialog/cosmic_powers",0);
    
    while(dial->lines != NULL){

        render_dialog_line(dial->lines);
        if(IsKeyPressed(KEY_C)){
            dial->lines = dial->lines->next;
            DrawScreen(map,player,delta);
        }
        
    }

}





int main(int argc, char** argv){

    world_node_t* map = init_world_node(0);
    player_t* player = init_player(24/2, 32/2,32,32,400);
    float delta;

    InitWindow(map->actual->x_dim * TILE_WIDTH, map->actual->y_dim * TILE_HEIGHT,"SQUARE");
    SetTargetFPS(60);

    while(!WindowShouldClose()){

        delta = GetFrameTime();

        DrawScreen(map,player,delta);
        PlayerInput(player,delta);
        update(&map,player,delta);
        if (IsKeyPressed(KEY_B))
        {
            dialog_event(map,player,delta);
        }
        
    }
}