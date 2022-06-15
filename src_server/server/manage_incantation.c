/*
** EPITECH PROJECT, 2022
** manage_incantation.c
** File description:
** manage incantation
*/

#include "commands.h"
#include "server.h"

int incantation(trantorians_t *trant, char **arg, zappy_data_t *data)
{
    if (check_incantation(data->map, trant) == -1)
        return (1);
    return (0);
}