/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** fork.c
*/

#include "server.h"
#include "zappy.h"

egg_t *init_egg(trantorians_t *trant, int nb_eggs, int freq)
{
    egg_t *egg = malloc(sizeof(egg_t));
    egg_list_t *egg_list = malloc(sizeof(egg_list_t));
    egg_list_t *cur = trant->team->eggs;

    if (!egg || !egg_list) {
        (egg) ? free(egg) : 0;
        return (NULL);
    }
    egg->trant = NULL;
    egg->tile = trant->tile;
    egg->next = NULL;
    egg->number = nb_eggs;
    egg->team = trant->team;
    egg->time_until_hatch = set_timespec(600, freq);
    egg_list->egg = egg;
    egg_list->next = NULL;
    while (cur || cur->next)
        cur = cur->next;
    (cur) ? (cur->next = egg_list) : (trant->team->eggs = egg_list);
    return (egg);
}

int fork_command(client_t *client, char **args, zappy_data_t *data)
{
    trantorians_t *trant = client->trant;
    team_t *team = trant->team;
    egg_list_t *list = team->eggs;
    egg_list_t *temp = NULL;
    egg_t *tmp = data->eggs;
    int nb_eggs = 0;

    while(tmp || tmp->next)  {
        nb_eggs ++;
        tmp = tmp->next;
    }
    if (tmp) {
        tmp->next = init_egg(trant, nb_eggs + 1, data->freq);
        temp = malloc(sizeof(egg_list_t));
        temp->egg = tmp->next;
        temp->next = list;
        team->eggs = temp;
    } else {
        data->eggs = init_egg(trant, nb_eggs + 1, data->freq);
        team->eggs = malloc(sizeof(egg_list_t));
        team->eggs->egg = data->eggs;
        team->eggs->next = NULL;
    }
    return (0);
}

bool player_spawn_for_egg(client_t *cli, server_t *info, team_t *team)
{
    char *line = NULL;

    if (!team || !team->eggs)
        return (false);
    cli->trant = create_add_trantoriant(cli, info->data, team->name);
    init_trantoriant(cli, info, team, true);
    for (egg_list_t *tmp = team->eggs; tmp; tmp = tmp->next) {
        if (!tmp->egg->trant) {
            cli->trant->egg_born = tmp->egg;
            cli->trant->egg_born->trant = cli->trant;
            tmp->egg = team->eggs->next;
            break;
        }
    }
    if (!cli->trant->egg_born) {
        asprintf(&line, "ko\n");
        cli->data_send = add_send(cli->data_send, line);
        free(line);
        free(cli->trant->team_name);
        free(cli->trant);
        cli->trant = NULL;
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
    while (tmp->next->egg != egg)
        tmp = tmp->next;
    to_del = tmp->next;
    tmp->next = tmp->next->next;
    free(to_del);
}

void kill_egg(egg_t *egg, zappy_data_t *data)
{
    egg_t *tmp = data->eggs;
    egg_t *to_del = NULL;

    death_hatched_egg(egg, data);
    delete_egg_in_team(egg, egg->team);
    if (egg == tmp) {
        data->eggs = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next != egg)
        tmp = tmp->next;
    tmp->next = egg->next;
    free(egg);
}
