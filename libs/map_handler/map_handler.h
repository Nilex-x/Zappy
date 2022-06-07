/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** map_handler
*/

#ifndef MAP_HANDLER_H_
    #define MAP_HANDLER_H_

    #define FOOD_DENSITY 0.5
    #define LINEMATE_DENSITY 0.3
    #define DERAUMERE_DENSITY 0.15
    #define SIBUR_DENSITY 0.1
    #define MENDIANE_DENSITY 0.1
    #define PHIRAS_DENSITY 0.08
    #define THYSTAME_DENSITY 0.05

    #include <stdlib.h>
    #include "zappy.h"

    extern const float density[7];
    extern const char *ressources[7];

    typedef struct trantorians_s trantorians_t;

    typedef struct tile_s {
        size_t x;
        size_t y;
        int *ressources;
        int nb_player;
        trantorians_t *trantorians;
    } tile_t;

    typedef struct map_s {
        size_t width;
        size_t height;
        tile_t ***tiles;
    } map_t;

    tile_t *init_tile(size_t x, size_t y);
    map_t *map_create(size_t width, size_t height);
    void free_trantorians(trantorians_t *trantorians);
    void free_tile(tile_t *tile);
    void free_map(map_t *map);

    void update_map_ressources(map_t *map);
    void init_map_ressources(map_t *map);

#endif /* !MAP_HANDLER_H_ */
