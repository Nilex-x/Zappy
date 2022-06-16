/*
** EPITECH PROJECT, 2022
** manage_trantorians.c
** File description:
** manahe_trantoriant
*/

#include "server.h"

trantorians_t *create_add_trantoriant(client_t *cli, zappy_data_t *data, char *team_name)
{
    trantorians_t *new = NULL;
    trantorians_t *temp = data->trants;

    new = malloc(sizeof(trantorians_t));
    if (!new)
        return (NULL);
    new->next = NULL;
    new->lvl = 1;
    new->is_alive = true;
    new->client = cli;
    new->team_name = strdup(team_name);
    new->inventory[0] = 10;
    for (int i = 1; i < 7; i++)
        new->inventory[i] = 0;
    if (!data->trants)
        data->trants = new;
    else {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
    return (new);
}

void free_trant(trantorians_t *trant)
{
    trantorians_t *next = NULL;

    while (trant) {
        next = trant->next;
        free(trant);
        trant = next;
    }
}
