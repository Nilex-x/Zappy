/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_events3
*/

#include "server.h"

void command_parameter(client_t *cli)
{
    cli->data_send = add_send(cli->data_send, "sbp\n");
}

void start_of_incantation(tile_t *tile, int level)
{
    client_t *client = tile->trantorians->client;
    char *str = NULL;

    asprintf(&str, "pic %d %d %d", tile->x, tile->y, level);
    for (trantorians_t *t = tile->trantorians; t; t = t->next) {
        if (t->lvl == level)
            asprintf(&str, "%s %d", str, t->client->socket);
    }
    asprintf(&str, "%s\n", str);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void end_of_incantation(tile_t *tile, int level)
{
    client_t *client = tile->trantorians->client;
    char *str = NULL;

    asprintf(&str, "pie %d %d %d\n", tile->x, tile->y, level);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void egg_laying(trantorians_t *trant)
{
    client_t *client = trant->client;
    char *str = NULL;

    asprintf(&str, "pfk %d\n", trant->client->socket);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void egg_layed(trantorians_t *t, egg_t *egg)
{
    client_t *client = t->client;
    char *str = NULL;

    asprintf(&str, "enw %d %d %d %d\n", egg->number, t->client->socket
    , t->tile->x, t->tile->y);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}
