/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_events
*/

#include "server.h"
#include <stdio.h>

void new_player_connect(trantorians_t *t, zappy_data_t *data)
{
    char *str = NULL;

    if (!t->client->socket)
        printf("Pas de chaussettes\n");
    if (!t->tile->x)
        printf("Pas de x dans tile\n");
    if (!t->tile->y)
        printf("Pas de y dans tile\n");
    if (!t->direction)
        printf("Pas de direction\n");
    if (!t->lvl)
        printf("Pas de lvl %d\n", t->lvl);
    if (!t->team->name)
        printf("Pas de team\n");
    asprintf(&str, "pnw #%d %ld %ld %d %d %s\n", t->client->socket,
    t->tile->x, t->tile->y, t->direction + 1, t->lvl, t->team->name);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
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
        free(str);
    }
}

void expulsion_message(trantorians_t *t, zappy_data_t *data)
{
    char *str = NULL;

    asprintf(&str, "pex %d\n", t->client->socket);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
    free(str);
}

void broadcast_message(trantorians_t *t, char **args, zappy_data_t *data)
{
    char *str = NULL;

    asprintf(&str, "pbc %d", t->client->socket);
    for (int i = 1; args[i]; i++) {
        str = strcatdup(str, args[i], " ");
    }
    str = strcatdup(str, "\n", "");
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
    free(str);
}

void ressource_dropping(trantorians_t *t, int obj, zappy_data_t *data)
{
    char *str = NULL;

    asprintf(&str, "pdr %d %d\n", t->client->socket, obj);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
    free(str);
}
