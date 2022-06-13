/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** fork.c
*/

#include "server.h"
#include "zappy.h"

int fork_command(client_t *client, char **args, zappy_data_t *data)
{
    (void) args;
    team_t *team = get_team_by_name(client->trant->team_name, data);
    team->player_max++;
    spawn_egg(client->trant);
    return (0);
}

int destroy_egg(server_t *info, team_t *team, egg_t *egg)
{
    if(egg->time_until_hatch <= 0 && team->nb_player < team->player_max) {
        team->player_max--;
        return (1);
    }
    client_t *head = info->list_client;
    for (;info->list_client; info->list_client = info->list_client->next) {
        if (!strcmp(info->list_client->team_name, team->name)
        && !info->list_client->trant) {
            info->list_client->trant = create_add_trantoriant(
                info->list_client, &info->data, team->name);
            trantorian_spawn_from_tile(info->list_client->trant, egg->tile);
            break;
        }
    }
    info->list_client = head;
    remove_egg_from_tile(egg);
    return (0);
}