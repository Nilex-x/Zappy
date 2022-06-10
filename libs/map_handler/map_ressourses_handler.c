/*
** EPITECH PROJECT * nb_tiles, 2022
** Zappy
** File description:
** init_map_ressourses
*/

#include "map_handler.h"
#include <stdlib.h>

char *get_items_on_tile(map_t *map, size_t x, size_t y)
{
    tile_t *c = map->tiles[x][y];
    char *line = NULL;

    for (size_t i = 0; i < c->nb_player; i++)
        (line) ? asprintf(&line, "%s player", line) : 
        asprintf(&line, "player");
    for (int i = 0; i < 7; i++)
        for (int j = 0; j < c->ressources[i]; j++)
            (line) ? asprintf(&line, "%s %s", ressources[i]) : 
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
        for (size_t k = 0; k < 7; k++) {
            missing[k] -= map->tiles[i / h][i % w]->ressources[k];
        }
    }
    for (size_t i = 0; i < 7; i++)
        for (size_t j = 0; j < missing[i]; j++)
            map->tiles[rand() % h][rand() % w]->ressources[i]++;
}

void init_map_ressources(map_t *map)
{
    size_t h = map->height;
    size_t w = map->width;

    for (size_t i = 0; i < 7; i++)
        for (size_t j = 0; j < density[i] * h * w; j++)
            map->tiles[rand() % h][rand() % w]->ressources[i]++;
}
