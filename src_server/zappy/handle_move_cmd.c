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
    int dir = trant->direction;

    (dir == NORTH) ? (new_y = (y != 0) ? y - 1 : map->height - 1) : 0;
    (dir == SOUTH) ? (new_y = (y != map->height - 1) ? y + 1 : 0) : 0;
    (dir == EAST) ? (new_x = (x != map->width - 1) ? x + 1 : 0) : 0;
    (dir == WEST) ? (new_x = (x != 0) ? x - 1 : map->width - 1) : 0;
    for (trantorians_t *c = map->tiles[x][y]->trantorians; c; c = c->next) {
        (c->next == trant) ? (c->next = trant->next) : 0;
        (c == trant) ? (map->tiles[x][y]->trantorians = trant->next) : 0;
    }
    trant->tile = map->tiles[new_x][new_y];
    trant->next = map->tiles[new_x][new_y]->trantorians;
    trant->tile->trantorians = trant;
    trant->tile->nb_player ++;
    map->tiles[x][y]->nb_player --;
}

int forward(client_t *client, char **arg, zappy_data_t *data)
{
    (void) arg;
    move_trantorian(data->map, client->trant);
    client->data_send = add_send(client->data_send, "ok\n");
    return 0;
}

int left(client_t *client, char **arg, zappy_data_t *data)
{
    (void) arg;
    (void) data;
    client->trant->direction = (client->trant->direction + 3) % 4;
    client->data_send = add_send(client->data_send, "ok\n");
    return 0;
}

int right(client_t *client, char **arg, zappy_data_t *data)
{
    (void) arg;
    (void) data;
    client->trant->direction = (client->trant->direction + 1) % 4;
    client->data_send = add_send(client->data_send, "ok\n");
    return 0;
}
