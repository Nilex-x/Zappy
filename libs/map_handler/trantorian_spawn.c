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

    rand_tile_line = map->tiles[rand() % map->width];
    rand_tile = rand_tile_line[rand() % map->height];
    list = rand_tile->trantorians;
    rand_tile->trantorians = trant;
    rand_tile->nb_player ++;
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
    tile->nb_player ++;
    trant->direction = rand() % 4;
}