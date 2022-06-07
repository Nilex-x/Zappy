/*
** EPITECH PROJECT, 2022
** manage_init.c
** File description:
** manage_init
*/

#define _GNU_SOURCE
#include "server.h"
#include <stdio.h>

void init_buff_client(client_t *node)
{
    node->buff_read = malloc(sizeof(buffer_t));
    if (!node->buff_read)
        return;
    init_buffer(node->buff_read, LENGTH_COMMAND);
}

int add_trantoriant(client_t *cli, server_t *info, char *cmd)
{
    team_t *team = get_team_by_name(clear_str(cmd), &info->data);
    char *line = NULL;

    printf("get team: %s exist: %d\n", cmd, team ? 1 : 0);
    cli->trant = create_add_trantoriant(cli, &info->data);
    // add spawn tile random
    asprintf(&line, "%d\n", (team->player_max - team->nb_player));
    cli->data_send = add_send(cli->data_send, line);
    free(line);
    return (0);
}

void handle_command(server_t *info, client_t *cli)
{
    char *value = NULL;
    value = read_to_buffer(cli->buff_read, '\n', LENGTH_COMMAND);
    if (!value || value[0] == '\n') {
        free(value);
        return;
    }
    printf("value client [%s]\n", value);
    if (!cli->trant)
        add_trantoriant(cli, info, value);
    else
        sort_command(cli, &info->data, value);
    free(value);
}
