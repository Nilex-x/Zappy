/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** eggs_handler.c
*/

#include "map_handler.h"
#include <time.h>

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

void egg_hatching_with_player(egg_t *egg, zappy_data_t *data)
{
    char *line = NULL;

    add_trantoriant_to_team(egg->trant, egg->trant->team, true);
    trantorian_spawn_from_tile(egg->trant, egg->tile);
    new_player_connect(egg->trant);
    asprintf(&line, "%d\n", (egg->team->player_max - egg->team->nb_player));
    egg->trant->cli->data_send = add_send(egg->trant->cli->data_send, line);
    free(line);
    asprintf(&line, "%d %d\n", info->data->width, info->data->height);
    cli->data_send = add_send(cli->data_send, line);
    free(line);
}
