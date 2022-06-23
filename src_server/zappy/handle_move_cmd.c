/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** handle_move_cmd
*/

#include "server.h"
#include <stdio.h>

void move_trantorian(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;
    size_t new_x = x;
    size_t new_y = y;
    trantorians_list_t *t = NULL;
    int dir = trant->direction;

    (dir == NORTH) ? (new_y = (y != 0) ? y - 1 : map->height - 1) : 0;
    (dir == SOUTH) ? (new_y = (y != map->height - 1) ? y + 1 : 0) : 0;
    (dir == EAST) ? (new_x = (x != map->width - 1) ? x + 1 : 0) : 0;
    (dir == WEST) ? (new_x = (x != 0) ? x - 1 : map->width - 1) : 0;
    for (trantorians_list_t *c = map->tiles[x][y]->trantorians; c; c = c->next) {
        if (c->next && c->next->trant == trant) {
            t = c->next;
            c->next = c->next->next;
        } else if (c->trant == trant) {
            t = c;
            map->tiles[x][y]->trantorians = c->next;
        }
    }
    trant->tile = map->tiles[new_x][new_y];
    t->next = map->tiles[new_x][new_y]->trantorians;
    trant->tile->trantorians = t;
    trant->tile->nb_player ++;
    map->tiles[x][y]->nb_player --;
}

int forward(client_t *client, char **arg, zappy_data_t *data)
{
    client_t *temp = client;

    move_trantorian(data->map, client->trant);
    client->data_send = add_send(client->data_send, "ok\n");
    while (temp->prev)
        temp = temp->prev;
    asprintf(&arg[1], "#%d", client->socket);
    for (client_t *c = temp; c; c = c->next)
        if (c->is_gui)
            gui_player_pos(c, arg, data);
    free(arg[1]);
    arg[1] = NULL;
    return 0;
}

int left(client_t *client, char **arg, zappy_data_t *data)
{
    client_t *temp = client;

    (void) data;
    client->trant->direction = (client->trant->direction + 3) % 4;
    client->data_send = add_send(client->data_send, "ok\n");
    asprintf(&arg[1], "#%d", client->socket);
    for (client_t *c = temp; c; c = c->next)
        if (c->is_gui)
            gui_player_pos(c, arg, data);
    free(arg[1]);
    arg[1] = NULL;
    return 0;
}

int right(client_t *client, char **arg, zappy_data_t *data)
{
    client_t *temp = client;

    (void) data;
    client->trant->direction = (client->trant->direction + 1) % 4;
    client->data_send = add_send(client->data_send, "ok\n");
    asprintf(&arg[1], "#%d", client->socket);
    for (client_t *c = temp; c; c = c->next)
        if (c->is_gui)
            gui_player_pos(c, arg, data);
    free(arg[1]);
    arg[1] = NULL;
    return 0;
}
