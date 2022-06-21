/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** manage_eject_cmd
*/

#include "server.h"

static const int ejected_from[4][4] = {
    {5, 7, 1, 3},
    {3, 5, 7, 1},
    {1, 3, 5, 7},
    {7, 1, 3, 5}
};

void send_ejected_message(trantorians_t *pusher, trantorians_t *pushed)
{
    char *msg = NULL;

    asprintf(&msg, "eject: %d\n", ejected_from[pusher->direction]
    [pushed->direction]);
    pushed->client->data_send = add_send(pushed->client->data_send, msg);
    free(msg);
}

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
