/*
** EPITECH PROJECT, 2022
** manage_map_time.c
** File description:
** manage_map_time
*/

#include "server.h"
#include <stdio.h>

void refill_map(server_t *info)
{
    struct timespec tosub = sub_timespec(info->time_ref, info->time_left);

    if (info->time_left.tv_sec <= 0 && info->time_left.tv_nsec <= 0) {
        printf("remove all\n");
        info->data->map->timeleft = sub_timespec(info->data->map->timeleft, info->time_ref);
    } else {
        printf("remove not\n");
        info->data->map->timeleft = sub_timespec(info->data->map->timeleft, tosub);
    }
    if (info->data->map->timeleft.tv_sec <= 0 &&
        info->data->map->timeleft.tv_nsec <= 0) {
        update_map_ressources(info->data->map);
        info->data->map->timeleft = set_timespec(20, info->data->freq);
        printf("Refill map\n");
    }
}