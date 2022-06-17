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
    new->client = cli;
    new->team_name = strdup(team_name);
    new->next = NULL;
    if (!data->trants)
        data->trants = new;
    else {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
    return (new);
}

void free_trantoriant(trantorians_t *trant)
{

    free(trant->team_name);
    while (trant->action) {
        free_array(trant->action->args);
        free(trant->action);
        trant->action = trant->action->next;
    }
    free(trant);
}

void remove_trantoriant(zappy_data_t *data, trantorians_t *torm)
{
    trantorians_t *temp = data->trants;
    trantorians_t *prev = NULL;

     if (temp == torm) {
        data->trants = temp->next;
        free_trantoriant(torm);
        return;
    }
    while (temp) {
        if (temp == torm) {
            prev->next = temp->next;
            free_trantoriant(torm);
            return;
        } else {
            prev = temp;
            temp = temp->next;
        }
    }
}

void free_trant(trantorians_t *trant)
{
    trantorians_t *next = NULL;

    while (trant) {
        next = trant->next;
        free(trant->team_name);
        free(trant);
        trant = next;
    }
}
