/*
** EPITECH PROJECT, 2022
** manager_server.c
** File description:
** manage_server
*/

#include "server.h"
#include <stdio.h>

static void sort_client(client_t *client, server_t *info)
{
    if (client->socket == info->fd_server) {
        accept_connect(info);
        return;
    }
    if (read_client(info, client) != -1)
        handle_command(info, client);
}

static void find_socket(server_t *info, client_t *cli)
{
    if (FD_ISSET(cli->socket, &info->efds)) {
        remove_client(info, cli->socket);
        return;
    }
    if (FD_ISSET(cli->socket, &info->rfds)) {
        sort_client(cli, info);
        return;
    }
    if (FD_ISSET(cli->socket, &info->wfds)) {
        write_client(info, cli->socket);
        return;
    }
    return;
}

static void sort_select_return(int ret, server_t *info)
{
    client_t *next = NULL;

    if (ret < 0) {
        perror("select()");
    }
    if (ret == 0) {
        printf(" = 0 / sec: %d, nsec: %d\n", info->time_ref.tv_sec, info->time_ref.tv_nsec);
        do_action(info);
        info->data->map->timeleft = sub_timespec(info->data->map->timeleft,
        info->time_ref);
        for (egg_t *egg = info->data->eggs; egg; egg = egg->next) {
            egg->time_until_hatch = sub_timespec(egg->time_until_hatch,
                info->time_ref);
        }
    }
    if (ret > 0) {
        printf(" > 0\n");
        select_interupt(info);
        for (client_t *temp = info->list_client; temp; temp = next) {
            next = temp->next;
            find_socket(info, temp);
        }
    }
}

void handler_connection(server_t *info)
{
    int retsel = 0;
    struct timeval time;


    while (1) {
        trantorians_t *curr = info->data->trants;
        clear_list(info);
        TIMESPEC_TO_TIMEVAL(&time, &info->time_left);
        retsel = select(info->max_fd + 1, &info->rfds, &info->wfds,
                        &info->efds, &time);
        TIMEVAL_TO_TIMESPEC(&time, &info->time_left);
        sort_select_return(retsel, info);
        refill_map(info);
        verif_life(info);
        find_win(info->data);
        while (curr != NULL) {
            printf("id:%d [%d][%d], lvl[%d], food[%d]\n", curr->client->socket, curr->tile->x, curr->tile->y, curr->lvl, curr->inventory[0]);
            curr = curr->next;
        }
        verif_egg_life(info);
    }
}
