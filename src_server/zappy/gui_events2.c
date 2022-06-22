/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_events2
*/

#include "server.h"
#include <stdio.h>

void ressource_collecting(trantorians_t *t, int obj)
{
    char *str = NULL;
    client_t *client = t->client;

    asprintf(&str, "pgt %d %d\n", t->client->socket, obj);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void death_of_a_player(trantorians_t *t)
{
    char *str = NULL;
    client_t *client = t->client;

    asprintf(&str, "pdi %d\n", t->client->socket);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void end_of_game(team_t *team, zappy_data_t *data)
{
    char *str = NULL;
    client_t *client = data->trants->client;

    asprintf(&str, "seg %s\n", team->name);
    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
    free(str);
}

void message_from_server(client_t *cli, char *str)
{
    client_t *client = cli;

    while (client->prev)
        client = client->prev;
    for (client_t *c = client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, str);
    }
}

void unknown_gui_command(client_t *cli)
{
    cli->data_send = add_send(cli->data_send, "suc\n");
}
