/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map_ressourses_handler
*/

#define _GNU_SOURCE
#include "lib.h"
#include "map_handler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

char *get_ressources(char *line, int i)
{
    if (line) {
        return (strcatdup(line, (char *) ressources[i], " "));
    } else {
        return (strdup(ressources[i]));
    }
}

char *get_items_on_tile(map_t *map, size_t x, size_t y)
{
    tile_t *c = map->tiles[x][y];
    char *line = NULL;

    for (int i = 0; i < c->nb_player; i++) {
        if (line)
            line = strcatdup(line, "player", " ");
        else
            line = strdup("player");
    }
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < c->ressources[i]; j++) {
            line = get_ressources(line, i);
        }
    }
    return (line) ? (line) : (strdup(""));
}

void update_map_ressources(map_t *map)
{
    size_t nb_tiles = map->width * map->height;
    size_t missing[7] = {FOOD_DENSITY * nb_tiles, LINEMATE_DENSITY * nb_tiles
    , DERAUMERE_DENSITY * nb_tiles, SIBUR_DENSITY * nb_tiles, MENDIANE_DENSITY
    * nb_tiles, PHIRAS_DENSITY * nb_tiles, THYSTAME_DENSITY * nb_tiles};

    for (size_t i = 0; i < nb_tiles; i++) {
        for (int k = 0; k < 7; k++)
            missing[k] -= ((size_t) map->tiles[i / map->height][i % map->height
            ]->ressources[k] > missing[k]) ? missing[k] : (size_t)
            map->tiles[i / map->height][i % map->height]->ressources[k];
    }
    for (size_t i = 0; i < 7; i++) {
        for (size_t j = 0; j < missing[i]; j++)
            map->tiles[rand() % map->width][rand() % map->height]->ressources[i]++;
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
