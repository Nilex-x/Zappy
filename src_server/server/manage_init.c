/*
** EPITECH PROJECT, 2022
** manage_init.c
** File description:
** manage_init
*/

#define _GNU_SOURCE
#include "server.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>

void init_buff_client(client_t *node)
{
    node->buff_read = malloc(sizeof(buffer_t));
    if (!node->buff_read)
        return;
    init_buffer(node->buff_read, LENGTH_COMMAND);
}

void init_data_struct(server_t *info)
{
    info->data = malloc(sizeof(zappy_data_t));
    if (!info->data)
        return;
    info->data->eggs = NULL;
    info->data->teams = NULL;
    info->data->trants = NULL;
    return;
}

void init_trantoriant(client_t *cli, server_t *info, team_t *team)
{
    cli->trant->timeleft = set_timespec(126, info->data->freq);
    cli->trant->lvl = 1;
    cli->trant->is_alive = true;
    cli->trant->inventory[0] = 10;
    cli->trant->action = NULL;
    for (int i = 1; i < 7; i++)
        cli->trant->inventory[i] = 0;
    trantorian_spawn(info->data->map, cli->trant);
    add_trantoriant_to_team(cli->trant, team);
}

void clear_list(server_t *info)
{
    client_t *temp = info->list_client;

    FD_ZERO(&info->wfds);
    FD_ZERO(&info->rfds);
    FD_ZERO(&info->efds);
    while (temp) {
        FD_SET(temp->socket, &info->efds);
        if (!temp->data_send)
            FD_SET(temp->socket, &info->rfds);
        if (temp->data_send)
            FD_SET(temp->socket, &info->wfds);
        temp = temp->next;
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
