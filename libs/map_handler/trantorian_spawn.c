/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** trantorian_spawn
*/

#include "map_handler.h"
#include <time.h>

void trantorian_spawn(map_t *map, trantorians_t *trant)
{
    tile_t **rand_tile_line = NULL;
    tile_t *rand_tile = NULL;
    trantorians_t *list = NULL;

    srand(time(NULL));
    rand_tile_line = map->tiles[rand() % map->height];
    srand(time(NULL));
    rand_tile = rand_tile_line[rand() % map->width];
    list = rand_tile->trantorians;
    rand_tile->trantorians = trant;
    trant->next = list;
    trant->tile = rand_tile;
    srand(time(NULL));
    trant->direction = rand() % 4;
}

void trantorian_spawn_from_tile(trantorians_t *trant, tile_t *tile)
{
    trantorians_t *list = tile->trantorians;

    tile->trantorians = trant;
    trant->next = list;
    trant->tile = tile;
    trant->direction = rand() % 4;
}