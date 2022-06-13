/*
** EPITECH PROJECT, 2022
** manage_time.c
** File description:
** manage_time
*/

#include "server.h"

struct timespec set_timespec(int time, int freq)
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
        ts.tv_sec--;
        ts.tv_nsec += 1000000000;
    }
    return (ts);
}

void select_interupt(server_t *info)
{
    struct timespec toSub = sub_timespec(info->time_ref, info->time_left);

    for (trantorians_t *t = info->data->trants; t; t = t->next) {
        sub_timespec(t->action->time_left, toSub);
    }
}

void get_shortest_time(server_t *info)
{
    struct timespec smallest = set_timespec(900, 1);

    for (trantorians_t *t = info->data->trants; t; t = t->next) {
        if (t->action && t->action->time_left.tv_sec < smallest.tv_sec 
        || (t->action->time_left.tv_sec == smallest.tv_sec 
        && t->action->time_left.tv_nsec < smallest.tv_nsec)) {
            smallest.tv_sec = t->action->time_left.tv_sec;
            smallest.tv_nsec = t->action->time_left.tv_nsec;
        }
    }
    info->time_left = smallest;
    info->time_ref = smallest;
}
