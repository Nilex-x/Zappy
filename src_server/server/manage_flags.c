/*
** EPITECH PROJECT, 2022
** manage_flags.c
** File description:
** manage_flags
*/

#include "server.h"
#include <unistd.h>
#include <stdio.h>

static int get_name_team(server_t *info, char **name_list, int index)
{
    while (name_list[index] && name_list[index][0] != '-') {
        printf("%d\n", info->data->max_teams_player);
        create_team(name_list[index], info->data);
        index++;
    }
    return (0);
}

static int verif_team_created(server_t *info)
{
    team_t *temp = info->data->teams;

    while (temp) {
        temp->player_max = info->data->max_teams_player;
        temp = temp->next;
    }
    return (0);
}

static int sort_flags(server_t *info, char **argv, int index, int ret)
{
    switch (ret) {
        case 'p':
            info->port = atoi(argv[index]);
            return (1);
        case 'x':
            info->data->width = atoi(argv[index]);
            return (1);
        case 'y':
            info->data->height = atoi(argv[index]);
            return (1);
        case 'f':
            info->data->freq = atoi(argv[index]);
            return (1);
        case 'c':
            info->data->max_teams_player = atoi(argv[index]);
            verif_team_created(info);
            return (1);
    }
    return (0);
}

static int init_zappy_data(zappy_data_t *data)
{
    data->freq = 100;
    data->width = 0;
    data->height = 0;
    data->teams = NULL;
    data->max_teams_player = 0;
    return (0);
}

int handle_flags(server_t *info, int argc, char **argv)
{
    int ret = getopt(argc, argv, "pxyncf");
    zappy_data_t *data = info->data;
    init_zappy_data(info->data);

    while (ret != -1) {
        if (ret == 'n')
            get_name_team(info, argv, optind);
        else
            sort_flags(info, argv, optind, ret);
        ret = getopt(argc, argv, "pxyncf");
    }
    if (data->height == 0 || data->width == 0 || data->max_teams_player == 0
    || !data->teams)
        exit(84);
    return (0);
}
