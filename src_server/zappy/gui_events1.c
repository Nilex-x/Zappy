/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_events
*/

#include "server.h"
#include <stdio.h>

void new_player_connect(trantorians_t *t)
{
    char *str = NULL;
    client_t *client = t->client;

    asprintf(&str, "pnw #%d %ld %ld %d %d %s\n", t->client->socket,
    t->tile->x, t->tile->y, t->direction + 1, t->lvl, t->team->name);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void gui_connect_new_player(client_t *gui, zappy_data_t *data)
{
    char *str = NULL;

    for (trantorians_t *t = data->trants; t; t = t->next) {
        asprintf(&str, "pnw #%d %ld %ld %d %d %s\n", t->client->socket,
        t->tile->x, t->tile->y, t->direction + 1, t->lvl, t->team->name);
        gui->data_send = add_send(gui->data_send, str);
    }
    free(str);
}

void expulsion_message(trantorians_t *t)
{
    char *str = NULL;
    client_t *client = t->client;

    asprintf(&str, "pex %d\n", t->client->socket);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void broadcast_message(trantorians_t *t, char **args, zappy_data_t *data)
{
    char *str = NULL;
    char *message = array_to_str(&args[1]);

    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, message);
        }
    }
    free(str);
}

void ressource_dropping(trantorians_t *t, int obj)
{
    char *str = NULL;
    client_t *client = t->client;

    asprintf(&str, "pdr %d %d\n", t->client->socket, obj);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}
