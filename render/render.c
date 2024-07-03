#include "../utils/utils.h"
#include "../player/player.h"
#include "../tilemap/tilemap.h"
#include "../misc/dialog/dialog.h"

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



void render_dialog_line(dialog_line_t* line){
    
    Rectangle dialog_box = {35, GetScreenHeight() - GetScreenHeight()/5, GetScreenWidth() - 70, GetScreenHeight()/5};

    BeginDrawing();
    DrawRectangleRec(dialog_box,BLACK);
    DrawRectangleLinesEx(dialog_box,3,MAROON);
    DrawText(TextFormat("%s",line->talker) , 35 + 5, (GetScreenHeight() - GetScreenHeight()/5), 20, WHITE );
    DrawText(TextFormat("%s",line->text) , 35 + 5, (GetScreenHeight() - GetScreenHeight()/5) + 45 , 20, WHITE );
    EndDrawing();

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
