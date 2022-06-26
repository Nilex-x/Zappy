/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** fork.c
*/

#include "server.h"
#include "zappy.h"
#include <stdio.h>

egg_t *init_egg(trantorians_t *trant, int nb_eggs, int freq)
{
    egg_t *egg = malloc(sizeof(egg_t));
    egg_list_t *egg_list = malloc(sizeof(egg_list_t));
    egg_list_t *cur = trant->team->eggs;

    if (!egg || !egg_list) {
        (egg) ? free(egg) : 0;
        (egg_list) ? free(egg_list) : 0;
        return (NULL);
    }
    egg->cli = NULL;
    egg->tile = trant->tile;
    egg->next = NULL;
    egg->number = nb_eggs;
    egg->team = trant->team;
    egg->time_until_hatch = set_timespec(600, freq);
    egg_list->egg = egg;
    egg_list->next = NULL;
    for(; cur && cur->next; cur = cur->next);
    (cur) ? (cur->next = egg_list) : (trant->team->eggs = egg_list);
    return (egg);
}

int fork_command(client_t *client, char **args, zappy_data_t *data)
{
    egg_t *tmp = data->eggs;
    int nb_eggs = 0;

    (void) args;
    printf("\033[0;34mTrantorian %d drop an egg\033[0m\n", client->socket);
    for (; tmp && tmp->next; nb_eggs++, tmp = tmp->next);
    if (tmp) {
        tmp->next = init_egg(client->trant, nb_eggs + 1, data->freq);
        egg_layed(client->trant, tmp->next, data);
    } else {
        data->eggs = init_egg(client->trant, nb_eggs + 1, data->freq);
        egg_layed(client->trant, data->eggs, data);
    }
    client->data_send = add_send(client->data_send, "ok\n");
    return (0);
}

bool added_in_egg(client_t *cli, server_t *info, team_t *team)
{
    (void) info;
    if (!team || !team->eggs) {
        return (false);
    }
    for (egg_list_t *tmp = team->eggs; tmp; tmp = tmp->next) {
        if (!tmp->egg->cli) {
            cli->egg = tmp->egg;
            cli->egg->cli = cli;
            break;
        }
    }
    if (!cli->egg) {
        cli->data_send = add_send(cli->data_send, "ko\n");
        return (false);
    }
    return (true);
}

void delete_egg_in_team(egg_t *egg, team_t *team)
{
    egg_list_t *tmp = team->eggs;
    egg_list_t *to_del = NULL;

    if (tmp->egg == egg) {
        team->eggs = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next->egg != egg || !tmp)
        tmp = tmp->next;
    if (!tmp)
        return;
    to_del = tmp->next;
    tmp->next = tmp->next->next;
    free(to_del);
}

