/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map_ressourses_handler
*/

#define _GNU_SOURCE
#include "map_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char *get_items_on_tile(map_t *map, size_t x, size_t y)
{
    tile_t *c = map->tiles[x][y];
    char *line = NULL;

    for (int i = 0; i < c->nb_player; i++)
        (line) ? asprintf(&line, "%s player", line) : 
        asprintf(&line, "player");
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < c->ressources[i]; j++)
            (line) ? asprintf(&line, "%s %s", line, ressources[i]) :
            asprintf(&line, "%s", ressources[i]);
    return (line) ? (line) : (strdup(""));
}

void update_map_ressources(map_t *map)
{
    size_t h = map->height;
    size_t w = map->width;
    size_t nb_tiles = w * h;
    size_t missing[7] = {FOOD_DENSITY * nb_tiles, LINEMATE_DENSITY * nb_tiles
    , DERAUMERE_DENSITY * nb_tiles, SIBUR_DENSITY * nb_tiles, MENDIANE_DENSITY
    * nb_tiles, PHIRAS_DENSITY * nb_tiles, THYSTAME_DENSITY * nb_tiles};

    for (size_t i = 0; i < h * w; i++) {
        for (int k = 0; k < 7; k++) {
            missing[k] -= map->tiles[i / w][i % h]->ressources[k];
        }
    }
    srand(time(NULL));
    for (size_t i = 0; i < 7; i++)
        for (size_t j = 0; j < missing[i]; j++) {
            map->tiles[rand() % w][rand() % h]->ressources[i]++;
        }
}

void init_map_ressources(map_t *map)
{
    size_t h = map->height;
    size_t w = map->width;

    srand(time(NULL));
    for (size_t i = 0; i < 7; i++) {
        for (size_t j = 0; j < density[i] * h * w; j++) {
            map->tiles[rand() % w][rand() % h]->ressources[i]++;
        }
    }
}
