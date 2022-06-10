/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** fork.c
*/

#include "server.h"
#include "zappy.h"

int fork_command(client_t *client, zappy_data_t *data, char *arg)
{
    (void) arg;
    team_t *team = get_team_by_name(client->trant->team_name, data);
    team->player_max++;
    spawn_egg(client->trant);
    return (0);
}

int destroy_egg(team_t *team, egg_t *egg)
{
    if(team->nb_player < team->player_max) {
        team->player_max--;
        return (1);
    }
    return (0);
}