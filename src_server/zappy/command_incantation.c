/*
** EPITECH PROJECT, 2022
** handle_incantation_cmd.c
** File description:
** handle incantation
*/

#include "server.h"
#include <stdio.h>

static const struct data_incant DATA_INCANT[] = {
    {
        .ressources_required = {1, 0, 0, 0, 0, 0},
        .trant_nb_required = 1
    },
    {
        .ressources_required = {1, 1, 1, 0, 0, 0},
        .trant_nb_required = 2
    },
    {
        .ressources_required = {2, 0, 1, 0, 2, 0},
        .trant_nb_required = 2
    },
    {
        .ressources_required = {1, 1, 2, 0, 1, 0},
        .trant_nb_required = 4
    },
    {
        .ressources_required = {1, 2, 1, 3, 0, 0},
        .trant_nb_required = 4
    },
    {
        .ressources_required = {1, 2, 3, 0, 1, 0},
        .trant_nb_required = 6
    },
    {
        .ressources_required = {2, 2, 2, 2, 2, 1},
        .trant_nb_required = 6
    }
};

static int check_incant_ressources(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;

    for (int i = 0; i < 7; i++)
        if (map->tiles[x][y]->ressources[i + 1] <
            DATA_INCANT[trant->lvl - 1].ressources_required[i])
            return (-1);
    return (0);
}

static int check_trant(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;
    int nb_trant = 0;

    for (trantorians_t *t = trant->tile->trantorians; t; t = t->next)
        if (t->lvl == trant->lvl)
            nb_trant++;
    if (nb_trant < DATA_INCANT[trant->lvl - 1].trant_nb_required)
        return (-1);
    return 0;
}

void start_incantation_for_everyone(trantorians_t *incanter)
{
    tile_t *tile = incanter->tile;
    trantorians_list_t *list = NULL;

    for (trantorians_t *t = tile->trantorians; t; t = t->next)
        if (t->lvl == incanter->lvl && t != incanter) {
            list = malloc(sizeof(trantorians_list_t));
            list->trant = t;
            list->next = incanter->incanting_with;
            incanter->incanting_with = list;
            list = NULL;
            t->is_incanting = true;
        }
}

int incantation(client_t *cli, char **arg, zappy_data_t *data)
{
    char *l = NULL;

    (void) arg;
    if (check_trant(data->map, cli->trant) == -1
    || check_incant_ressources(data->map, cli->trant) == -1) {
        cli->data_send = add_send(cli->data_send, "ko\n");
        return (-1);
    }
    if (cli->trant->action->time_left.tv_sec > 0
    && cli->trant->action->time_left.tv_nsec > 0) {
        start_of_incantation(cli->trant->tile, cli->trant->lvl);
        start_incantation_for_everyone(cli->trant);
        cli->data_send = add_send(cli->data_send, "Elevation underway\n");
        return (0);
    }
    cli->trant->lvl ++;
    asprintf(&l, "Current level: %d\n", cli->trant->lvl);
    end_of_incantation(cli->trant->tile, cli->trant->lvl);
    cli->data_send = add_send(cli->data_send, l);
    for (trantorians_list_t *t = cli->trant->incanting_with; t; t = t->next) {
        t->trant->client->data_send = add_send(t->trant->client->data_send, l);
        t->trant->is_incanting = false;
        t->trant->lvl++;
    }
    free(l);
    return (1);
}