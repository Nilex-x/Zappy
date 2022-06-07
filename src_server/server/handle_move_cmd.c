/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** handle_move_cmd
*/

#include "server.h"

void move_trantorian(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;
    size_t new_x = x;
    size_t new_y = y;

    if (trant->direction == NORTH)
        new_y = (y != 0) ? y - 1 : map->height - 1;
    if (trant->direction == SOUTH)
        new_y = (y != map->height - 1) ? y + 1 : 0;
    if (trant->direction == EAST)
        new_x = (x != map->width - 1) ? x + 1 : 0;
    if (trant->direction == WEST)
        new_x = (x != 0) ? x - 1 : map->width - 1;
    for (trantorians_t *c = map->tiles[x][y]->trantorians; c; c = c->next) {
        (c->next == trant) ? (c->next = trant->next) : 0;
        (c == trant) ? (map->tiles[x][y]->trantorians = trant->next) : 0;
    }
    trant->tile = map->tiles[new_x][new_y];
    trant->next = map->tiles[new_x][new_y]->trantorians;
    trant->tile->trantorians = trant;
}

int move(trantorians_t *trant, char **arg, zappy_data_t *data)
{
    move_trantorian(data->map, trant);
    (void) arg;
    return 0;
}
