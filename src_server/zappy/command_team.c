/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_team
*/

#include "server.h"
#include <stdio.h>

int team_unused_slot(trantorians_t *trant, char **args, zappy_data_t *data)
{
    int unused_slot = (trant->team->player_max - trant->team->nb_player);
    char *buff;

    (void) data;
    (void) args;
    asprintf(&buff, "%d\n", unused_slot);
    trant->client->data_send = add_send(trant->client->data_send, buff);
    return 0;
}
