#ifndef TILEMAP_H
#define TILEMAP_H

#define TILE_WIDTH 64
#define TILE_HEIGHT 64


#include "../utils/utils.h"

typedef enum update_direction{
    NORTH,
    SOUTH,
    WEST,
    EAST
}update_direction_t; 

typedef enum tile_type{

    GROUND,
    ACID,
    WILL

}tile_type_t;

typedef struct tile{

    tile_type_t type;
    void* entity_on_tile;

}tile_t;

typedef struct tilemap{
   

    tile_t* tiles;
    uint16_t tile_width;
    uint16_t tile_height;
    uint16_t x_dim;
    uint16_t y_dim;
    int id;

}tilemap_t;

typedef struct world{

    struct world* north;
    struct world* south;
    struct world* east;
    struct world* west;
    tilemap_t* actual;
    

} world_node_t;


Color TileColor(tile_t tile);

Vector2 tile_cords_from_pos(Vector2 pos, tilemap_t* map);

tilemap_t* init_tilemap(uint16_t x_size, uint16_t y_size,int old_id);

world_node_t* init_world_node(int old_tile_id);

void connect_tilemap(update_direction_t direction, world_node_t* starting_node, world_node_t* connect_to);

void update_tilemap(update_direction_t direction, world_node_t** world);

#endif