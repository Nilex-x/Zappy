/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_commands_2
*/

#include "server.h"
#include <stdio.h>

int gui_player_pos(client_t *cli, char **args, zappy_data_t *data)
{
    int player_nb = 0;
    char *line = NULL;
    trantorians_t *curr = NULL;

    if (len_array(args) != 2) {
        cli->data_send = add_send(cli->data_send, "ko\n");
        return 1;
    }
    player_nb = atoi(args[1]);
    for (client_t *c = data->server->list_client; c; c = c->next) {
        if (c->socket == player_nb) {
            curr = c->trant;
            asprintf(&line, "ppo %d %ld %ld %d\n", player_nb, curr->tile->x
            , curr->tile->y, curr->direction + 1);
            cli->data_send = add_send(cli->data_send, line);
            free(line);
            return 0;
        }
    }
    return 1;
}

int gui_player_lvl(client_t *cli, char **args, zappy_data_t *data)
{
    int player_nb = 0;
    char *line = NULL;
    trantorians_t *curr = NULL;

    if (len_array(args) != 2) {
        cli->data_send = add_send(cli->data_send, "ko\n");
        return 1;
    }
    player_nb = atoi(args[1] + 1);
    for (client_t *c = data->trants->client; c; c = c->next)
        if (c->socket == player_nb) {
            curr = c->trant;
            asprintf(&line, "plv %d %d\n", player_nb, curr->lvl);
            cli->data_send = add_send(cli->data_send, line);
            free(line);
            return 0;
        }
    return 1;
}

int gui_player_inventory(client_t *cli, char **args, zappy_data_t *data)
{
    int player_nb = 0;
    char *line = NULL;
    trantorians_t *curr = NULL;

    if (len_array(args) != 2) {
        cli->data_send = add_send(cli->data_send, "ko\n");
        return 1;
    }
    player_nb = atoi(args[1] + 1);
    for (client_t *c = data->trants->client; c; c = c->next)
        if (c->socket == player_nb) {
            curr = c->trant;
            asprintf(&line, "pin %d %ld %ld %d %d %d %d %d %d %d\n", player_nb, curr->tile->x
            , curr->tile->y, curr->inventory[0], curr->inventory[1]
            , curr->inventory[2], curr->inventory[3], curr->inventory[4]
            , curr->inventory[5], curr->inventory[6]);
            cli->data_send = add_send(cli->data_send, line);
            free(line);
            return 0;
        }
    return 1;
}

int gui_time_unit_request(client_t *cli, char **args, zappy_data_t *data)
{
    char *line = NULL;

    (void) args;
    asprintf(&line, "sgt %d\n", data->freq);
    cli->data_send = add_send(cli->data_send, line);
    free(line);
    return 0;
}

int gui_time_unit_modif(client_t *cli, char **args, zappy_data_t *data)
{
    int new_freq = 0;
    char *line = NULL;

    if (len_array(args) != 2) {
        cli->data_send = add_send(cli->data_send, "ko\n");
        return 0;
    }
    new_freq = atoi(args[1]);
    asprintf(&line, "sgt %d\n", data->freq);
    cli->data_send = add_send(cli->data_send, line);
    free(line);
    data->freq = new_freq;
    return 0;
}
