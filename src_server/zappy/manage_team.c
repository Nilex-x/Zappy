/*
** EPITECH PROJECT, 2022
** manage_team.c
** File description:
** manage_team
*/

#include "zappy.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

team_t *get_team_by_name(char *name, zappy_data_t *data)
{
    team_t *temp = data->teams;

    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

team_t *add_trantoriant_to_team(trantorians_t *trant, team_t *team)
{
    trantorians_list_t *new = NULL;
    trantorians_list_t *temp = team->list;

    new = malloc(sizeof(trantorians_list_t));
    if (!new)
        return (NULL);
    team->nb_player++;
    new->trant = trant;
    new->next = NULL;
    trant->team = team;
    if (!team->list)
        team->list = new;
    else {
        while (temp->next)
            temp = temp->next;
        temp->next = new;
    }
    return (team);
}

team_t *create_team(char *name, zappy_data_t *data)
{
    team_t *new = malloc(sizeof(team_t));
    team_t *temp = data->teams;

    if (!new)
        return (NULL);
    new->name = strdup(name);
    new->nb_player = 0;
    new->player_max = data->max_teams_player;
    new->next = NULL;
    new->list = NULL;
    if (!data->teams) {
        data->teams = new;
        return (new);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new;
    return (new);
}

void remove_trant_in_team(team_t *team, trantorians_t *torm)
{
    trantorians_list_t *temp = team->list;
    trantorians_list_t *prev = NULL;

    team->nb_player--;
    if (!torm)
        return;
    if (temp->trant == torm) {
        team->list = temp->next;
        free(temp);
        return;
    }
    while (temp) {
        if (temp->trant == torm) {
            prev->next = temp->next;
            free(temp);
            return;
        }
        prev = temp;
        temp = temp->next;
    }
}

void free_teams(team_t *teams)
{
    team_t *next = NULL;
    trantorians_list_t *next_list = NULL;
    trantorians_list_t *list = teams->list;

    while (teams) {
        next = teams->next;
        free(teams->name);
        while (list) {
            next_list = list->next;
            free(list);
            list = next_list;
        }
        free(teams);
        teams = next;
    }
    return;
}
