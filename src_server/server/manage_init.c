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

void init_data_struct(server_t *info)
{
    info->data = malloc(sizeof(zappy_data_t));
    if (!info->data)
        return;
    info->data->eggs = NULL;
    info->data->teams = NULL;
    info->data->trants = NULL;
    return;
}

void init_trantoriant(client_t *cli, server_t *info, team_t *team)
{
    cli->trant->timeleft = set_timespec(126, info->data->freq);
    cli->trant->lvl = 1;
    cli->trant->is_alive = true;
    cli->trant->inventory[0] = 10;
    cli->trant->action = NULL;
    for (int i = 1; i < 7; i++)
        cli->trant->inventory[i] = 0;
    trantorian_spawn(info->data->map, cli->trant);
    add_trantoriant_to_team(cli->trant, team);
}

void add_trantoriant(client_t *cli, server_t *info, char *cmd)
{
    team_t *team = get_team_by_name(clear_str(cmd), info->data);
    char *line = NULL;

    if (!team || team->nb_player == team->player_max) {
        cli->data_send = add_send(cli->data_send, (!team) ? "unkown team\n" :
        "team is already full please wait until a client disconnect " \
        "or fork\n");
    } else {
        cli->trant = create_add_trantoriant(cli, info->data, team->name);
        asprintf(&line, "%d\n", (team->player_max - team->nb_player));
        cli->data_send = add_send(cli->data_send, line);
        free(line);
        init_trantoriant(cli, info, team);
        asprintf(&line, "%d %d\n", info->data->width, info->data->height);
        cli->data_send = add_send(cli->data_send, line);
        free(line);
        new_player_connect(cli->trant);
    }
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
    if (strcmp(value, "gui\n") == 0) {
        gui_connect_new_player(cli, info->data);
        cli->is_gui = true;
        return;
    }
    if (!cli->trant && !cli->is_gui)
        add_trantoriant(cli, info, value);
    else
        sort_command(cli, info->data, value);
    free(value);
}
