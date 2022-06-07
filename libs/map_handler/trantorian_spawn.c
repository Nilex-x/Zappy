/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** trantorian_spawn
*/

#include "map_handler.h"

void trantorian_spawn(map_t *map, trantorians_t *trant)
{
    tile_t *rand_tile = map->tiles[rand() % map->height][rand() % map->width];
    trantorians_t *list = rand_tile->trantorians;

    rand_tile->trantorians = trant;
    trant->next = list;
    trant->tile = rand_tile;
    trant->direction = rand() % 4;
}
