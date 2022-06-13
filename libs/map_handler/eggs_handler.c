/*
** EPITECH PROJECT, 2021
** Zappy
** File description:
** eggs_handler.c
*/

#include "map_handler.h"
#include <time.h>

void spawn_egg(trantorians_t *trant)
{
    egg_t *egg = malloc(sizeof(egg_t));

    if (!egg)
        return;
    egg->tile = trant->tile;
    egg->next = trant->tile->eggs;
    egg->time_until_hatch = 600;
    egg->team_name = trant->team_name;
    trant->tile->eggs = egg;
}

void remove_egg_from_tile(egg_t *egg)
{
    egg->tile->eggs = egg->next;
    free(egg);
}

void free_eggs(egg_t *egg)
{
    if (!egg)
        return;
    free_eggs(egg->next);
    free(egg);
}