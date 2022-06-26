/*
** EPITECH PROJECT, 2022
** manage_trantorians.c
** File description:
** manahe_trantoriant
*/

#include "server.h"
#include <stdio.h>

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

static void free_trantoriant(trantorians_t *trant)
{
    action_t *temp = NULL;

    remove_trant_in_team(trant->team, trant, (trant->egg_born) ? true : false);
    free(trant->team_name);
    while (trant->action) {
        temp = trant->action;
        trant->action = trant->action->next;
        free_array(temp->args);
        free(temp);
    }
    free(trant);
}

void remove_trantoriant(zappy_data_t *data, trantorians_t *torm)
{
    trantorians_t *temp = data->trants;
    trantorians_t *prev = NULL;

    if (!torm)
        return;
    printf("\033[1;31mTrantorian %d level %d joined the god of death\033[0m\n", temp->client->socket, temp->lvl);
    death_of_a_player(torm, data);
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

void free_trants(trantorians_t *trantorians)
{
    trantorians_t *next = NULL;

    while (trantorians) {
        next = trantorians->next;
        free_trantoriant(trantorians);
        trantorians = next;
    }
}
