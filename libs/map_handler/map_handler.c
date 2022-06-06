/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map_handler
*/

#include "map_handler.h"

const float density[7] = {FOOD_DENSITY, LINEMATE_DENSITY, DERAUMERE_DENSITY, SIBUR_DENSITY, MENDIANE_DENSITY, PHIRAS_DENSITY, THYSTAME_DENSITY};
const char *ressources[7] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

tile_t *init_tile(size_t x, size_t y)
{
    tile_t *tile = malloc(sizeof(tile_t));

    if (!tile)
        return (NULL);
    tile->x = x;
    tile->y = y;
    tile->ressources = calloc(7, sizeof(int));
    tile->nb_player = 0;
    tile->trantorians = NULL;
    return (tile);
}

map_t *map_create(size_t width, size_t height)
{
    map_t *map = malloc(sizeof(map_t));

    if (map == NULL)
        return (NULL);
    map->width = width;
    map->height = height;
    map->tiles = malloc(sizeof(tile_t *) * height);
    if (map->tiles == NULL)
        return (NULL);
    for (size_t i = 0; i < height; i++) {
        map->tiles[i] = malloc(sizeof(tile_t) * width);
        if (map->tiles[i] == NULL)
            return (NULL);
        for (size_t j = 0; j < width; j++) {
            map->tiles[i][j] = init_tile(i, j);
        }
    }
    init_map_ressources(map);
    return (map);
}

void free_trantorians(trantorians_t *trantorians)
{
    if (trantorians == NULL)
        return;
    free_trantorians(trantorians->next);
    free(trantorians);
}

void free_tile(tile_t *tile)
{
    if (tile == NULL)
        return;
    free(tile->ressources);
    free(tile->trantorians);
    free(tile);
}

void free_map(map_t *map)
{
    for (size_t i = 0; i < map->height; i++) {
        for (size_t j = 0; j < map->width; j++) {
            free(map->tiles[i][j]);
        }
        free(map->tiles[i]);
    }
    free(map->tiles);
    free(map);
}
