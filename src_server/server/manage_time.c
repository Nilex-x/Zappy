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
    if (ts.tv_sec < 0)
        ts.tv_sec = 0;
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

    info->data->map->timeleft = sub_timespec(info->data->map->timeleft,
        to_sub);
    for (trantorians_t *t = info->data->trants; t; t = t->next) {
        if (t->action)
            t->action->time_left = sub_timespec(t->action->time_left, to_sub);
        t->timeleft = sub_timespec(t->timeleft, to_sub);
    }
    for (egg_t *egg = info->data->eggs; egg; egg = egg->next) {
        egg->time_until_hatch = sub_timespec(egg->time_until_hatch, to_sub);
    }
}

void find_time(struct timespec *small, struct timespec value)
{
    if ((value.tv_sec < small->tv_sec) ||
    (value.tv_sec == small->tv_sec && value.tv_nsec < small->tv_nsec)) {
        small->tv_sec = value.tv_sec;
        small->tv_nsec = value.tv_nsec;
    }
}

void get_shortest_time(server_t *info)
{
    struct timespec smallest = set_timespec(900, info->data->freq);

    for (trantorians_t *t = info->data->trants; t; t = t->next) {
        if (t->action && !t->is_incanting)
            find_time(&smallest, t->action->time_left);
        find_time(&smallest, t->timeleft);
    }
    for (egg_t *e = info->data->eggs; e; e = e->next)
        find_time(&smallest, e->time_until_hatch);
    find_time(&smallest, info->data->map->timeleft);
    if (smallest.tv_sec < 0)
        smallest.tv_sec = 0;
    info->time_left = smallest;
    info->time_ref = smallest;
}
