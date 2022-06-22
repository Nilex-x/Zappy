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

static void find_socket(server_t *info)
{
    client_t *next = NULL;

    for (client_t *temp = info->list_client; temp; temp = next) {
        next = temp->next;
        if (FD_ISSET(temp->socket, &info->efds))
            remove_client(info, temp->socket);
        if (FD_ISSET(temp->socket, &info->rfds))
            sort_client(temp, info);
        if (FD_ISSET(temp->socket, &info->wfds))
            write_client(info, temp->socket);
    }
    return;
}

static void sort_select_return(int ret, server_t *info)
{
    if (ret < 0) {
        perror("select()");
        exit(84);
    }
    if (ret == 0)
        do_action(info);
    if (ret > 0) {
        select_interupt(info);
        find_socket(info);
    }
}

void handler_connection(server_t *info)
{
    int retsel = 0;
    struct timeval time;

    while (1) {
        clear_list(info);
        TIMESPEC_TO_TIMEVAL(&time, &info->time_left);
        retsel = select(info->max_fd + 1, &info->rfds, &info->wfds,
                        &info->efds, &time);
        TIMEVAL_TO_TIMESPEC(&time, &info->time_left);
        sort_select_return(retsel, info);
        refill_map(info);
        verif_life(info);
        find_win(info->data);
    }
}
