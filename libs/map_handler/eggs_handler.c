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

