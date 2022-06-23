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
    write(2, "UPDATE MAP\n", 12);
    size_t nb_tiles = map->width * map->height;
    size_t missing[7] = {FOOD_DENSITY * nb_tiles, LINEMATE_DENSITY * nb_tiles
    , DERAUMERE_DENSITY * nb_tiles, SIBUR_DENSITY * nb_tiles, MENDIANE_DENSITY
    * nb_tiles, PHIRAS_DENSITY * nb_tiles, THYSTAME_DENSITY * nb_tiles};

    for (size_t i = 0; i < 7; i++)
        printf("MISSING %ld -> %d\n", missing[i], i);
    write(2, "LOOP MAP 1\n", 12);
    for (size_t i = 0; i < nb_tiles; i++) {
        for (int k = 0; k < 7; k++) {
            missing[k] -= map->tiles[i / map->width][i % map->height]->ressources[k];
        }
    }
    write(2, "LOOP MAP 2\n", 12);
    write(2, "LOOP MAP 3\n", 12);
    for (size_t i = 0; i < 7; i++) {
        printf("Big LOOP\n");
        for (size_t j = 0; j < missing[i] && j < 10; j++) {
            printf("MISSING missing: %ld -> j: %d ==> i: %d\n", missing[i], j, i);
            map->tiles[rand() % map->width][rand() % map->height]->ressources[i]++;
        }
    }
    write(2, "LEAVE MAP\n", 11);
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
