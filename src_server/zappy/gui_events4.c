/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_events4
*/

#include "server.h"
#include <stdio.h>

void egg_hatching(egg_t *egg, tile_t *tile)
{
    client_t *client = tile->trantorians->trant->client;
    char *str = NULL;

    asprintf(&str, "eht %d\n", egg->number);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void player_connexion_for_egg(trantorians_t *t, egg_t *egg)
{
    client_t *client = t->client;
    char *str = NULL;

    asprintf(&str, "ebo %d\n", egg->number);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void death_hatched_egg(egg_t *egg, zappy_data_t *data)
{
    client_t *client = data->trants->client;
    char *str = NULL;

    asprintf(&str, "edi %d\n", egg->number);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void gui_player_level(client_t *client, server_t *info)
{
    char *line = NULL;

    asprintf(&line, "plv %d %d\n", client->socket, client->trant->lvl);
    for (client_t *c = info->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, line);
        }
    }
    free(line);
    return;
}