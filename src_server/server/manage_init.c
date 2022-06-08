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

    printf("enter\n");
    if (!team) {
        cli->data_send = add_send(cli->data_send, "unkown team\n");
        return (0);
    }
    if (team->nb_player == team->player_max) {
        printf("team->nb_player = %d\nplayer_max = %d\n",team->nb_player, team->player_max);
        cli->data_send = add_send(cli->data_send, "teams is already full\n");
        return (0);
    }
    printf("now we are here\n");
    printf("get team: %s exist: %d\n", cmd, team ? 1 : 0);
    cli->trant = create_add_trantoriant(cli, &info->data);
    asprintf(&line, "%d\n", (team->player_max - team->nb_player));
    cli->data_send = add_send(cli->data_send, line);
    free(line);
    trantorian_spawn(info->data.map, cli->trant);
    add_trantoriant_to_team(cli->trant, team);
    asprintf(&line, "%ld %ld\n", cli->trant->tile->x,  cli->trant->tile->y);
    cli->data_send = add_send(cli->data_send, line);
    free(line);
    printf("new trant team name: %s x: %ld y: %ld\n", team->name, cli->trant->tile->x, cli->trant->tile->y);
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
    if(strstr(value, "inventory")) {
        display_inventory(cli->trant, NULL, info->data);
    }
    printf("value client [%s]\n", value);
    if (!cli->trant)
        add_trantoriant(cli, info, value);
    else
        sort_command(cli, &info->data, value);
    free(value);
}
