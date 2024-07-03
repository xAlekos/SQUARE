#ifndef RENDER_H
#define RENDER_H

#include "../utils/utils.h"
#include "../player/player.h"
#include "../tilemap/tilemap.h"
#include "../misc/dialog/dialog.h"

void render_tilemap(tilemap_t* map);

void render_player(player_t* player);

void render_dialog_line(dialog_line_t* line);

void highlight_tile(player_t* player, tilemap_t* map);

void draw_ui(player_t* player, tilemap_t* map);

void DrawScreen(world_node_t* map , player_t* player, float delta);

#endif