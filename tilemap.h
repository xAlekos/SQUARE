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
    int id;

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

tilemap_t* init_tilemap(uint16_t x_size, uint16_t y_size,int old_id){
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
    new_tilemap->id = old_id + 1;
    return new_tilemap;

}

world_node_t* init_world_node(int old_tile_id){
    
    world_node_t* new_world = malloc(sizeof(world_node_t));
    new_world->north = NULL;
    new_world->east = NULL;
    new_world->west = NULL;
    new_world->south = NULL;
    new_world->actual = init_tilemap(12,16,old_tile_id);
    return new_world;

}

/*
uint8_t update_position(update_direction_t direction, world_node_t** starting_position){
    //TODO AGGIUNGERE CHECK SE PROVA AD ANDARE A NULL
    switch (direction)
    {
    case NORTH: 
        if((*starting_position)->north == NULL)
            return 1;
        *starting_position = (*starting_position)->north;
        break;
    case SOUTH:
        if((*starting_position)->south == NULL)
            return 1;
        *starting_position = (*starting_position)->south;
        break;
    case WEST:
        if((*starting_position)->west == NULL)
            return 1;
        *starting_position = (*starting_position)->west;
        break;
    case EAST:
        if((*starting_position)->east == NULL)
            return 1;
        *starting_position = (*starting_position)->east;
    default:
        break;
    }
    return 0;
}

uint8_t connect_to_direction(update_direction_t direction, world_node_t* connect, world_node_t* to){
    //TODO AGGIUNGERE CHECK SE PROVA AD ANDARE A NULL
    switch (direction)
    {
    case NORTH: 
        connect->north = to;
        break;
    case SOUTH:
        connect->south = to;
        break;
    case WEST:
        connect->west = to;
        break;
    case EAST:
        connect->east = to;
    default:
        break;
    }
    return 0;
}*/

/*
void connect_tilemap(update_direction_t direction, world_node_t* starting_node, world_node_t* connect_to){

    update_direction_t move_order_a[4];
    update_direction_t move_order_b[4];
    update_direction_t connect_order_a[4];
    update_direction_t  connect_order_b[4];
    

    switch (direction){
        
    case NORTH:

        move_order_a[0] = EAST;
        move_order_a[1] = NORTH;
        move_order_a[2] = NORTH;
        move_order_a[3] = WEST;

        move_order_b[0] = WEST;
        move_order_b[1] = NORTH;
        move_order_b[2] = NORTH;
        move_order_b[3] = EAST;

        connect_order_a[0] = WEST;
        connect_order_a[1] = EAST;
        connect_order_a[2] = SOUTH;
        connect_order_a[3] = NORTH;

        connect_order_b[0] = EAST;
        connect_order_b[1] = WEST;
        connect_order_b[2] = SOUTH;
        connect_order_b[3] = NORTH;

        break;

    case SOUTH:

        move_order_a[0] = EAST;
        move_order_a[1] = SOUTH;
        move_order_a[2] = SOUTH;
        move_order_a[3] = WEST;

        move_order_b[0] = WEST;
        move_order_b[1] = SOUTH;
        move_order_b[2] = SOUTH;
        move_order_b[3] = EAST;

        connect_order_a[0] = WEST;
        connect_order_a[1] = EAST;
        connect_order_a[2] = NORTH;
        connect_order_a[3] = SOUTH;

        connect_order_b[0] = EAST;
        connect_order_b[1] = WEST;
        connect_order_b[2] = NORTH;
        connect_order_b[3] = SOUTH;
        break;

    case WEST:

        move_order_a[0] = NORTH;
        move_order_a[1] = WEST;
        move_order_a[2] = WEST;
        move_order_a[3] = SOUTH;

        move_order_b[0] = SOUTH;
        move_order_b[1] = WEST;
        move_order_b[2] = WEST;
        move_order_b[3] = NORTH;

        connect_order_a[0] = SOUTH;
        connect_order_a[1] = NORTH;
        connect_order_a[2] = EAST;
        connect_order_a[3] = WEST;

        connect_order_b[0] = NORTH;
        connect_order_b[1] = SOUTH;
        connect_order_b[2] = EAST;
        connect_order_b[3] = WEST;
        break;
    case EAST:

        move_order_a[0] = NORTH;
        move_order_a[1] = EAST;
        move_order_a[2] = EAST;
        move_order_a[3] = SOUTH;

        move_order_b[0] = SOUTH;
        move_order_b[1] = EAST;
        move_order_b[2] = EAST;
        move_order_b[3] = NORTH;

        connect_order_a[0] = SOUTH;
        connect_order_a[1] = NORTH;
        connect_order_a[2] = WEST;
        connect_order_a[3] = EAST;

        connect_order_b[0] = NORTH;
        connect_order_b[1] = SOUTH;
        connect_order_b[2] = WEST;
        connect_order_b[3] = EAST;
        break;
    default:
        break;
    }

    int j = 0;

    for(int i = 0;i<4;i++){
        
        if(update_position(move_order_a[i],&starting_node) == 1)
            break;
        if(i == 1 || i == 3){
        connect_to_direction(connect_order_a[j++],starting_node,connect_to);
        connect_to_direction(connect_order_a[j++],connect_to,starting_node);
        }            
    }

    j = 0;

    for(int i = 0;i<4;i++){
        
        if(update_position(move_order_b[i],&starting_node) == 1)
            break;
        if(i == 1 || i == 3){
        connect_to_direction(connect_order_b[j++],starting_node,connect_to);
        connect_to_direction(connect_order_b[j++],connect_to,starting_node);  
        }          
    }

    j = 0;
}
*/

void connect_tilemap(update_direction_t direction, world_node_t* starting_node, world_node_t* connect_to){
    //Questa funzione è un crimine contro l'umanità
    world_node_t* position = starting_node;

    switch(direction){
        case NORTH:
            if(position->east != NULL){                             // EST, NORD, CONNETTILO AD OVEST, CONNETTITI AD EST, NORD, OVEST, CONETTILO A SUD, CONNETITI A NORD
                position = position->east;
                if(position->north != NULL){
                    position = position->north;
                    position->west = connect_to;
                    connect_to->east = position;
                    if(position->north != NULL){
                        position = position->north;
                        if(position->west != NULL){
                            position = position->west;
                            position->south = connect_to;
                            connect_to->north = position;
                        }
                    }
                }
            }
            position = starting_node;
            if(position->west != NULL){
                position = position->west;
                if(position->north != NULL){
                    position = position->north;
                    position->east = connect_to;
                    connect_to->west = position;
                    if(position->north != NULL){
                        position = position->north;
                        if(position->east != NULL){
                            position = position->east;
                            position->south = connect_to;
                            connect_to->north = position;
                        }
                    }
                }
            }
            break;

        case SOUTH:
            if(position->east != NULL){
                position = position->east;
                if(position->south != NULL){
                    position = position->south;
                    position->west = connect_to;
                    connect_to->east = position;
                    if(position->south != NULL){
                        position = position->south;
                        if(position->west != NULL){
                            position = position->west;
                            position->north = connect_to;
                            connect_to->south = position;
                        }
                    }
                }
            }
            position = starting_node;
            if(position->west != NULL){
                position = position->west;
                if(position->south != NULL){
                    position = position->south;
                    position->east = connect_to;
                    connect_to->west = position;
                    if(position->south != NULL){
                        position = position->south;
                        if(position->east != NULL){
                            position = position->east;
                            position->north = connect_to;
                            connect_to->south = position;
                        }
                    }
                }
            }
            break;

        case EAST:
            if(position->north != NULL){
                position = position->north;
                if(position->east != NULL){
                    position = position->east;
                    position->south = connect_to;
                    connect_to->north = position;
                    if(position->east != NULL){
                        position = position->east;
                        if(position->south != NULL){
                            position = position->south;
                            position->west = connect_to;
                            connect_to->east = position;
                        }
                    }
                }
            }
            position = starting_node;
            if(position->south != NULL){
                position = position->south;
                if(position->east != NULL){
                    position = position->east;
                    position->north = connect_to;
                    connect_to->south = position;
                    if(position->east != NULL){
                        position = position->east;
                        if(position->north != NULL){
                            position = position->north;
                            position->west = connect_to;
                            connect_to->east = position;
                        }
                    }
                }
            }
            break;

        case WEST:
            if(position->north != NULL){
                position = position->north;
                if(position->west != NULL){
                    position = position->west;
                    position->south = connect_to;
                    connect_to->north = position;
                    if(position->west != NULL){
                        position = position->west;
                        if(position->south != NULL){
                            position = position->south;
                            position->east = connect_to;
                            connect_to->west = position;
                        }
                    }
                }
            }
            position = starting_node;
            if(position->south != NULL){
                position = position->south;
                if(position->west != NULL){
                    position = position->west;
                    position->north = connect_to;
                    connect_to->south = position;
                    if(position->west != NULL){
                        position = position->west;
                        if(position->north != NULL){
                            position = position->north;
                            position->east = connect_to;
                            connect_to->west = position;
                        }
                    }
                }
            }
            break;
    }

}

void update_tilemap(update_direction_t direction, world_node_t** world){

    world_node_t* starting_node = *world;

    switch(direction){
        case NORTH:
            if(starting_node->north == NULL){
                starting_node->north = init_world_node((*world)->actual->id);
                connect_tilemap(NORTH,starting_node,starting_node->north);
            }
            starting_node->north->south = starting_node;
            *world = starting_node->north;
            
            

        break;

        case SOUTH:
            if((*world)->south == NULL){
                (*world)->south = init_world_node((*world)->actual->id);
                connect_tilemap(SOUTH,starting_node,starting_node->south);
            }
            (*world)->south->north = *world;
            *world = (*world)->south;
            
        break;

        case EAST:
            if((*world)->east == NULL){
                (*world)->east = init_world_node((*world)->actual->id);
                connect_tilemap(EAST,starting_node,starting_node->east);
            }
            (*world)->east->west = *world;
            *world = (*world)->east;
           
        break;

        case WEST:
            if((*world)->west == NULL){
                (*world)->west = init_world_node((*world)->actual->id);
                connect_tilemap(WEST,starting_node,starting_node->west);
            }
            (*world)->west->east = *world;
            *world = (*world)->west;
            
        break;
    }


}