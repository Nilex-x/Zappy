/*
** EPITECH PROJECT, 2022
** manage_flags.c
** File description:
** manage_flags
*/

#include "server.h"
#include <unistd.h>

int get_name_team(server_t *info, char **name_list, int index)
{
    while (name_list[index] && name_list[index][0] != '-') {
        printf("i: %d, value: %s\n", optind, name_list[index]);
        create_team(name_list[index], info->data);
        index++;
    }
    return (0);
}

int sort_flags(server_t *info, char **argv, int index, int ret)
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
            return (1);
        default:
            return (0);
    }
}

int handle_flags(server_t *info, int argc, char **argv)
{
    int ret = getopt(argc, argv, "pxync");
    bool find = false;

    while (ret != -1) {
        printf("ret: %d index: %d, value: %s\n", ret, optind, argv[optind]);
        if (ret == 'n') {
            get_name_team(info, argv, optind);
        } else if (!find && sort_flags(info, argv, optind, ret) == 0) {
            fprintf(stderr, "Usage: %s -p port -x width -y height "
            "-n name1 name2 ... -c clientsNb -f freq\n", argv[0]);
            exit(84);
        }
        ret = getopt(argc, argv, "pxyncf");
    }
    return (0);
}