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

    #define bool unsigned int
    #define true 1
    #define false 0

    #include <stdlib.h>

    const float density[7] = {FOOD_DENSITY, LINEMATE_DENSITY, DERAUMERE_DENSITY, SIBUR_DENSITY, MENDIANE_DENSITY, PHIRAS_DENSITY, THYSTAME_DENSITY};
    const char *ressources[7] = {"food", "linemate", "deraumere", "sibur", "mendiane", "phiras", "thystame"};

    typedef enum directions {
        NORTH,
        EAST,
        SOUTH,
        WEST
    } direction_t;

    typedef struct trantorians_s {
        bool is_alive;
        unsigned int life_left;
        int food;
        int linemate;
        int deraumere;
        int sibur;
        int mendiane;
        int phiras;
        int thystame;
        direction_t direction;
        struct trantorians_s *next;
    } trantorians_t;

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
