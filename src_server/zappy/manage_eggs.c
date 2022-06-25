/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** manage_eggs
*/

#include "server.h"
#include <stdio.h>

void egg_hatching_with_player(egg_t *egg, zappy_data_t *data)
{
    char *line = NULL;

    printf("\033[0;34mEgg hatching with a new trantorian !\033[0m\n");
    egg->cli->trant = create_add_trantoriant(egg->cli, data, egg->team->name);
    asprintf(&line, "%d\n", (egg->team->player_max - egg->team->nb_player));
    egg->cli->data_send = add_send(egg->cli->data_send, line);
    free(line);
    add_trantoriant_to_team(egg->cli->trant, egg->team, true);
    trantorian_spawn_from_tile(egg->cli->trant, egg->tile);
    new_player_connect(egg->cli->trant, data);
    asprintf(&line, "%d %d\n", data->width, data->height);
    egg->cli->data_send = add_send(egg->cli->data_send, line);
    free(line);
}

void free_eggs(egg_t **egg)
{
    egg_t *tmp = *egg;

    while (tmp) {
        tmp = tmp->next;
        free(*egg);
        *egg = tmp;
    }
}

void free_eggs_list(egg_list_t **egg_list)
{
    egg_list_t *tmp = *egg_list;

    while (tmp) {
        tmp = tmp->next;
        free(*egg_list);
        *egg_list = tmp;
    }
}

static int remove_egg_in_team(egg_t *torm, team_t *team)
{
    egg_list_t *next = NULL;
    egg_list_t *prev = NULL;


    printf("Start find egg\n");
    if (!team->eggs)
        return;
    printf("egg is in temm\n");
    if (torm == team->eggs->egg) {
        printf("first egg in temm\n");
        next = team->eggs;
        team->eggs = team->eggs->next;
        free(next);
        return;
    }
    for (egg_list_t *egg = team->eggs; egg; egg = next) {
        printf("find free egg in team\n");
        next = egg->next;
        if (egg->egg == torm) {
            printf("find egg in team\n");
            prev->next = egg->next;
            free(egg);
            break;
        }
        prev = egg;
    }
    return;
}

void kill_egg(egg_t *egg, zappy_data_t *data)
{
    egg_t *tmp = data->eggs;

    printf("\033[0;31mEgg dead !\033[0m\n");
    death_hatched_egg(egg, data);
    delete_egg_in_team(egg, egg->team);
    if (egg == tmp) {
        printf("HERE\n");
        data->eggs = tmp->next;
        free(tmp);
        return;
    }
    while (tmp->next != egg)
        tmp = tmp->next;
    tmp->next = egg->next;
    free(egg);
}
