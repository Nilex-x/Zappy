/*
** EPITECH PROJECT, 2022
** handle_incantation_cmd.c
** File description:
** handle incantation
*/

#include "commands.h"
#include "map_handler.h"

static const struct data_incant DATA_INCANT[] = {
    {
        .ressources_required = {1, 0, 0, 0, 0, 0},
        .trant_nb_required = 1,
        .trant_min_lvl_required = 1,
        .trant_max_lvl_required = 1
    },
    {
        .ressources_required = {1, 1, 1, 0, 0, 0},
        .trant_nb_required = 2,
        .trant_min_lvl_required = 2,
        .trant_max_lvl_required = 3
    },
    {
        .ressources_required = {2, 0, 1, 0, 2, 0},
        .trant_nb_required = 2,
        .trant_min_lvl_required = 2,
        .trant_max_lvl_required = 3
    },
    {
        .ressources_required = {1, 1, 2, 0, 1, 0},
        .trant_nb_required = 4,
        .trant_min_lvl_required = 4,
        .trant_max_lvl_required = 5
    },
    {
        .ressources_required = {1, 2, 1, 3, 0, 0},
        .trant_nb_required = 4,
        .trant_min_lvl_required = 4,
        .trant_max_lvl_required = 5
    },
    {
        .ressources_required = {1, 2, 3, 0, 1, 0},
        .trant_nb_required = 6,
        .trant_min_lvl_required = 6,
        .trant_max_lvl_required = 7
    },
    {
        .ressources_required = {2, 2, 2, 2, 2, 1},
        .trant_nb_required = 6,
        .trant_min_lvl_required = 6,
        .trant_max_lvl_required = 7
    }
};

static int check_incant_ressources(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;

    for (int x = 0; x < 7; x++)
        if (map->tiles[x][y]->ressources[x + 1] <
            DATA_INCANT[trant->lvl - 1].ressources_required[x])
            return (-1);
    return (0);
}

static int check_trant_required_level(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;

    for (trantorians_t *c = map->tiles[x][y]->trantorians; c; c = c->next) {
        if (DATA_INCANT[trant->lvl - 1].trant_min_lvl_required > c->lvl &&
            DATA_INCANT[trant->lvl - 1].trant_max_lvl_required < c->lvl)
            return (-1);
        if (trant->lvl != c->lvl && check_incant_ressources(map, c) == -1)
            return (-1);
    }
    return (0);
}

static int check_trant_required_nb(map_t *map, trantorians_t *trant)
{
    size_t x = trant->tile->x;
    size_t y = trant->tile->y;
    int trant_on_tile = 0;

    for (trantorians_t *c = map->tiles[x][y]->trantorians; c; c = c->next)
        trant_on_tile++;
    if (trant_on_tile != DATA_INCANT[trant->lvl - 1].trant_nb_required)
        return (-1);
    return (0);
}

int check_incantation(map_t *map, trantorians_t *trant)
{
    if (check_trant_required_nb(map, trant) == -1)
        return (-1);
    if (check_incant_ressources(map, trant) == -1)
        return (-1);
    if (check_trant_required_level(map, trant) == -1)
        return (-1);
    return (0);
}