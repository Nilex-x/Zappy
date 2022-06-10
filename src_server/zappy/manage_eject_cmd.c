/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** manage_eject_cmd
*/

#include "server.h"

int eject(trantorians_t *trant, char **arg, zappy_data_t *data)
{
    action_t *curr = NULL;
    bool ejected = false;

    for (trantorians_t *c = trant->tile->trantorians; c; c = c->next)
        if (trant != c) {
            c->direction = (c->direction + 2) % 4;
            move_trantorian(data->map, c);
            c->direction = (c->direction + 2) % 4;
            curr = c->action;
            (curr) ? (c->action = curr->next) : 0;
            (curr) ? free(curr) : 0;
            curr = NULL;
            ejected = true;
        }
    if (ejected)
        trant->client->data_send = add_send(trant->client->data_send, "ok\n");
    else
        trant->client->data_send = add_send(trant->client->data_send, "ko\n");
    return (1 - ejected);
}
