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
