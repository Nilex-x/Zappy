/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_events2
*/

#include "server.h"
#include <stdio.h>

void ressource_collecting(trantorians_t *t, int obj, zappy_data_t *data)
{
    char *str = NULL;

    asprintf(&str, "pgt %d %d\n", t->client->socket, obj);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
    free(str);
}

void death_of_a_player(trantorians_t *t, zappy_data_t *data)
{
    char *str = NULL;

    asprintf(&str, "pdi %d\n", t->client->socket);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
    free(str);
}

void end_of_game(team_t *team, zappy_data_t *data)
{
    char *str = NULL;

    asprintf(&str, "seg %s\n", team->name);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
    free(str);
}

void message_from_server(client_t *cli, char *str, zappy_data_t *data)
{
    (void) cli;
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->is_gui) {
            c->data_send = add_send(c->data_send, str);
        }
    }
}

void unknown_gui_command(client_t *cli)
{
    cli->data_send = add_send(cli->data_send, "suc\n");
}
