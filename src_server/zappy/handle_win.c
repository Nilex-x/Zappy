/*
** EPITECH PROJECT, 2022
** handle_win.c
** File description:
** handle_win
*/

#include "zappy.h"

static int find_win_team(team_t *team)
{
    trantorians_list_t *list = team->list;
    int nb = 0;
    int nb_player_max = 0;

    while (list) {
        if (list->trant->lvl == 8)
            nb_player_max++;
        nb++;
        list = list->next;
    }

    if (nb_player_max == nb)
        return (1);
    else
        return (0);
}

int find_win(zappy_data_t *data)
{
    team_t *team = data->teams;

    while (team) {
        if (find_win_team(team) == 1)
            return (1);
        team = team->next;
    }

    return (0);
}