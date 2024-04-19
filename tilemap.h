#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define TILE_WIDTH 64
#define TILE_HEIGHT 64

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

}tilemap_t;

typedef struct world{

    struct world* north;
    struct world* south;
    struct world* east;
    struct world* west;
    tilemap_t* actual;
    

} world_node_t;


Color TileColor(tile_t tile){
    
    switch(tile.type){
        case GROUND:
            return BLACK;
        case ACID:
            return GREEN;
        case WILL:
            return BLUE;
        default:
            return PURPLE;
    }
}

Vector2 tile_cords_from_pos(Vector2 pos, tilemap_t* map){

    Vector2 tile_pos;
    tile_pos.x = (int)(pos.x / map->tile_width);
    tile_pos.y = (int)(pos.y / map->tile_height);
    return tile_pos;
}

tilemap_t* init_tilemap(uint16_t x_size, uint16_t y_size){
    srand(time(NULL));
    tilemap_t* new_tilemap = calloc(1,sizeof(tilemap_t));
    tile_t* newmap = calloc(x_size*y_size, sizeof(tile_t));
    for(int i = 0; i<rand() % 10; i++)
        newmap[rand() % x_size* y_size].type = ACID;
    for(int i = 0; i<rand() % 15; i++)
        newmap[rand() % (x_size* y_size)].type = WILL;
    new_tilemap->tiles = newmap;
    new_tilemap->tile_height = TILE_HEIGHT;
    new_tilemap->tile_width = TILE_WIDTH;
    new_tilemap->x_dim = x_size;
    new_tilemap->y_dim = y_size;
    return new_tilemap;

}

world_node_t* init_world_node(){
    
    world_node_t* new_world = malloc(sizeof(world_node_t));
    new_world->north = NULL;
    new_world->east = NULL;
    new_world->west = NULL;
    new_world->south = NULL;
    new_world->actual = init_tilemap(12,16);
    return new_world;

}

void update_tilemap(update_direction_t direction, world_node_t** world){

    switch(direction){
        case NORTH:
            if((*world)->north == NULL){
                (*world)->north = init_world_node();
            }
            (*world)->north->south = *world;
            *world = (*world)->north;
        break;

        case SOUTH:
            if((*world)->south == NULL){
                (*world)->south = init_world_node();
            }
            (*world)->south->north = *world;
            *world = (*world)->south;
        break;

        case EAST:
            if((*world)->east == NULL){
                (*world)->east = init_world_node();
            }
            (*world)->east->west = *world;
            *world = (*world)->east;
        break;

        case WEST:
            if((*world)->west == NULL){
                (*world)->west = init_world_node();
            }
            (*world)->west->east = *world;
            *world = (*world)->west;
        break;
    }


}