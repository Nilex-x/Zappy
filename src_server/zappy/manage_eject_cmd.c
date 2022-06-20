/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** manage_eject_cmd
*/

#include "server.h"

int eject(client_t *client, char **arg, zappy_data_t *data)
{
    trantorians_t *trant = client->trant;
    bool ejected = false;
    int dir;

    for (trantorians_t *c = trant->tile->trantorians; c; c = c->next)
        if (trant != c) {
            dir = c->direction;
            c->direction = trant->direction;
            move_trantorian(data->map, c);
            c->direction = dir;
            ejected = true;
            expulsion_message(c);
        }
    if (ejected)
        client->data_send = add_send(client->data_send, "ok\n");
    else
        client->data_send = add_send(client->data_send, "ko\n");
    return (1 - ejected);
}
