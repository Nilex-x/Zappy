/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_team
*/

#include "server.h"
#include <stdio.h>

int team_unused_slot(client_t *client, char **args, zappy_data_t *data)
{
	int unused_slot = (client->trant->team->player_max - client->trant->team->nb_player);
	char *buff;

    (void) args;
    (void) data;
	asprintf(&buff, "%d\n", unused_slot);
	client->data_send = add_send(client->data_send, buff);
	free(buff);
	return 0;
}
