/*
** EPITECH PROJECT, 2022
** manage_team.c
** File description:
** manage_team
*/

#include "zappy.h"
#include <stdlib.h>
#include <string.h>

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
    if (!data->teams) {
        data->teams = new;
        return (new);
    }
    while (temp->next)
        temp = temp->next;
    temp->next = new;
    return (new);
}

void free_teams(team_t *teams)
{
    team_t *next = NULL;

    while (teams) {
        next = teams->next;
        free(teams->name);
        free(teams);
        teams = next;
    }
    return;
}