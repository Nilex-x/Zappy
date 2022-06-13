/*
** EPITECH PROJECT, 2022
** manage_time.c
** File description:
** manage_time
*/

#include "server.h"

int get_the_shortest_cmd(server_t *info)
{
    trantorians_t *temp = info->data->trants;
    int shortest = 0;

    while (temp) {
        if (temp->action && (temp->action->time_left < shortest || shortest == 0) )
            shortest = temp->action->time_left;
        temp = temp->next;
    }
    return (shortest);
}

// struct timeval set_timeval(int time, int freq)
// {

// }
