/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** manage_eject_cmd
*/

#include "server.h"

int eject(trantorians_t *trant, char **arg, zappy_data_t *data)
{
    bool ejected = false;
    int dir;

    for (trantorians_t *c = trant->tile->trantorians; c; c = c->next)
        if (trant != c) {
            dir = c->direction;
            c->direction = trant->direction;
            move_trantorian(data->map, c);
            c->direction = dir;
            ejected = true;
        }
    if (ejected)
        trant->client->data_send = add_send(trant->client->data_send, "ok\n");
    else
        trant->client->data_send = add_send(trant->client->data_send, "ko\n");
    return (1 - ejected);
}
