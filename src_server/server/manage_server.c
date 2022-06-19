/*
** EPITECH PROJECT, 2022
** manager_server.c
** File description:
** manage_server
*/

#include "server.h"
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>

void clear_list(server_t *info)
{
    client_t *temp = info->list_client;

    FD_ZERO(&info->wfds);
    FD_ZERO(&info->rfds);
    FD_ZERO(&info->efds);
    while (temp) {
        printf("temp: %d\n", temp->socket);
        FD_SET(temp->socket, &info->efds);
        if (!temp->data_send)
            FD_SET(temp->socket, &info->rfds);
        if (temp->data_send)
            FD_SET(temp->socket, &info->wfds);
        temp = temp->next;
    }
}

void sort_client(client_t *client, server_t *info)
{
    if (client->socket == info->fd_server) {
        accept_connect(info);
        return;
    }
    if (read_client(info, client) != -1)
        handle_command(info, client);
}

void find_socket(server_t *info)
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
        if (retsel < 0) {
            perror("select()");
            exit(84);
        }
        if (retsel == 0)
            do_action(info);
        if (retsel > 0) {
            select_interupt(info);
            find_socket(info);
        }
        verif_life(info);
        get_shortest_time(info);
    }
}

int create_socket(server_t *info)
{
    struct sockaddr_in my_addr;
    size_t len = sizeof(struct sockaddr_in);

    info->fd_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (info->fd_server == -1)
        return -1;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons((uint16_t) info->port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(info->fd_server, (struct sockaddr *) &my_addr, len) == -1) {
        perror("Bind()");
        return -1;
    }
    if (listen(info->fd_server, NB_LISTEN) == -1)
        return -1;
    info->max_fd = info->fd_server;
    FD_ZERO(&info->rfds);
    FD_ZERO(&info->wfds);
    FD_ZERO(&info->efds);
    FD_SET(info->fd_server, &info->rfds);
    return (0);
}
