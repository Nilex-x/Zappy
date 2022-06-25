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
    if (info->data->map->timeleft.tv_sec <= 0 &&
        info->data->map->timeleft.tv_nsec <= 0) {
        update_map_ressources(info->data->map);
        info->data->map->timeleft = set_timespec(20, info->data->freq);
    }
}

void verif_life(server_t *info)
{
    trantorians_t *temp = info->data->trants;

    while (temp) {
        if (temp->inventory[0] <= 0) {
            printf("\033[0;31mTrantorian dead\033[0m\n");
            temp->client->is_quit = true;
            temp->client->data_send = add_send(temp->client->data_send,
            "dead\n");
            death_of_a_player(temp, info->data);
        } else if (temp->timeleft.tv_sec <= 0 && temp->timeleft.tv_nsec <= 0) {
            temp->inventory[0]--;
            temp->timeleft = set_timespec(126, info->data->freq);
            printf("ID: [%d], FOOD: [%d]\n", temp->client->socket, temp->inventory[0]);
        }
        temp = temp->next;
    }
    get_shortest_time(info);
}