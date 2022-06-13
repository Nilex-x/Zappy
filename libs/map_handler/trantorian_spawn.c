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
    tile_t *rand_tile = map->tiles[rand() % map->height][rand() % map->width];
    trantorians_t *list = rand_tile->trantorians;

    srand(time(NULL));
    rand_tile->trantorians = trant;
    trant->next = list;
    trant->tile = rand_tile;
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