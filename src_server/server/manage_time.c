/*
** EPITECH PROJECT, 2022
** manage_time.c
** File description:
** manage_time
*/

#include "server.h"
#include <stdio.h>

struct timespec set_timespec(long long int time, long long int freq)
{
    struct timespec ts;

    ts.tv_sec = time / freq;
    ts.tv_nsec = (time % freq) * 1000000000 / freq;
    return (ts);
}

struct timespec sub_timespec(struct timespec ts1, struct timespec ts2)
{
    struct timespec ts;

    ts.tv_sec = ts1.tv_sec - ts2.tv_sec;
    ts.tv_nsec = ts1.tv_nsec - ts2.tv_nsec;
    if (ts.tv_nsec < 0) {
        if (ts.tv_sec > 0)
            ts.tv_sec--;
        ts.tv_nsec += 1000000000;
    }
    return (ts);
}

void select_interupt(server_t *info)
{
    struct timespec to_sub = sub_timespec(info->time_ref, info->time_left);

    for (trantorians_t *t = info->data->trants; t; t = t->next) {
        if (t->action)
            t->action->time_left = sub_timespec(t->action->time_left, to_sub);
        t->timeleft = sub_timespec(t->timeleft, to_sub);
    }
}

void get_shortest_time(server_t *info)
{
    struct timespec smallest = set_timespec(900, 1);

    for (trantorians_t *t = info->data->trants; t; t = t->next) {
        if ((t->action && t->action->time_left.tv_sec < smallest.tv_sec)
        || ((t->action && t->action->time_left.tv_sec == smallest.tv_sec
        && t->action->time_left.tv_nsec < smallest.tv_nsec))) {
            smallest.tv_sec = t->action->time_left.tv_sec;
            smallest.tv_nsec = t->action->time_left.tv_nsec;
        }
        if ((t->timeleft.tv_sec < smallest.tv_sec) ||
        (t->timeleft.tv_sec == smallest.tv_sec &&
        t->timeleft.tv_nsec < smallest.tv_nsec)) {
            smallest.tv_sec = t->timeleft.tv_sec;
            smallest.tv_nsec = t->timeleft.tv_nsec;
        }
    }
    printf("sec: %ld | nsec: %ld\n", smallest.tv_sec, smallest.tv_nsec);
    if (smallest.tv_sec < 0)
        smallest.tv_sec = 0;
    info->time_left = smallest;
    info->time_ref = smallest;
}

void verif_life(server_t *info)
{
    trantorians_t *temp = info->data->trants;

    while (temp) {
        if (temp->inventory[0] <= 0) {
            printf("kill trantoriant client: %d\n", temp->client->socket);
            temp->client->is_quit = true;
            temp->client->data_send = add_send(temp->client->data_send,
            "dead\n");
            death_of_a_player(temp);
        } else if (temp->timeleft.tv_sec <= 0 && temp->timeleft.tv_nsec <= 0) {
            printf("remove food client: %d - food: %d\n", temp->client->socket, temp->inventory[0]);
            temp->inventory[0]--;
            temp->timeleft = set_timespec(126, info->data->freq);
        }
        temp = temp->next;
    }
    get_shortest_time(info);
}
