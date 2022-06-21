/*
** EPITECH PROJECT, 2022
** handle_client.c
** File description:
** handler_client
*/

#include "server.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>

void init_client(server_t *info)
{
    client_t *list_client = NULL;

    list_client = malloc(sizeof(client_t));
    if (!list_client)
        return;
    list_client->next = NULL;
    list_client->prev = NULL;
    list_client->status = READ;
    list_client->socket = info->fd_server;
    list_client->is_quit = false;
    list_client->is_gui = false;
    list_client->data_send = NULL;
    init_buff_client(list_client);
    info->list_client = list_client;
}

client_t *add_client(server_t *info, int client)
{
    client_t *temp = info->list_client;
    client_t *node = NULL;

    node = malloc(sizeof(client_t));
    if (!node)
        return NULL;
    while (temp->next)
        temp = temp->next;
    temp->next = node;
    node->socket = client;
    node->prev = temp;
    node->next = NULL;
    node->status = READ;
    node->data_send = NULL;
    node->is_quit = false;
    node->is_gui = false;
    init_buff_client(node);
    return (node);
}

client_t *find_client(server_t *info, int client)
{
    client_t *temp = info->list_client;

    while (temp) {
        if (temp->socket == client)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

void remove_client(server_t *info, int client)
{
    for (client_t *temp = info->list_client; temp; temp = temp->next) {
        if (temp->socket == client && info->list_client->socket == client) {
            info->list_client = info->list_client->next;
            remove_trantoriant(info->data, temp->trant);
            free(temp->buff_read);
            free_data_send(temp->data_send);
            free(temp);
            return;
        }
        if (temp->socket == client) {
            temp->prev->next = temp->next;
            (temp->next) ? (temp->next->prev = temp->prev) : 0;
            remove_trantoriant(info->data, temp->trant);
            free(temp->buff_read);
            free_data_send(temp->data_send);
            free(temp);
            return;
        }
    }
}

void accept_connect(server_t *info)
{
    struct sockaddr_in client;
    socklen_t len = sizeof(struct sockaddr_in);
    client_t *new_client = NULL;
    int incomming_fd = accept(info->fd_server, (struct sockaddr *) &client, \
                                &len);
    FD_SET(incomming_fd, &info->wfds);
    printf("incoming: %d\n",incomming_fd);
    new_client = add_client(info, incomming_fd);
    new_client->data_send = add_send(new_client->data_send, "WELCOME\n");
    new_client->status = WRITE;
    new_client->trant = NULL;
    if (incomming_fd > info->max_fd)
        info->max_fd = incomming_fd;
}
