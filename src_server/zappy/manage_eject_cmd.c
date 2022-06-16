/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** manage_eject_cmd
*/

#include "server.h"

int eject(client_t *client, char **arg, zappy_data_t *data)
{
    action_t *curr = NULL;
    bool ejected = false;

    (void) arg;
    for (trantorians_t *c = client->trant->tile->trantorians; c; c = c->next)
        if (client->trant != c) {
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
        client->data_send = add_send(client->data_send, "ok\n");
    else
        client->data_send = add_send(client->data_send, "ko\n");
    return (1 - ejected);
}
