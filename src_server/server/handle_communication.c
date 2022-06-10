/*
** EPITECH PROJECT, 2022
** handle_communication.c
** File description:
** handle_comunication
*/

#include "server.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int read_client(server_t *info, client_t *client)
{
    char *read_buffer = NULL;
    int read_value = -1;

    read_buffer = malloc(sizeof(char) * LENGTH_COMMAND);
    if (!read_buffer)
        return (-1);
    read_value = read(client->socket, read_buffer, LENGTH_COMMAND);
    if (read_value == -1) {
        free(read_buffer);
        return (-1);
    }
    if (read_value == 0) {
        remove_client(info, client->socket);
        free(read_buffer);
        return (-1);
    }
    read_buffer[read_value] = '\0';
    add_to_write(client->buff_read, read_buffer, LENGTH_COMMAND);
    free(read_buffer);
    return (0);
}

void write_client(server_t *info, int s_client)
{
    int w_value = 1;
    client_t *client = find_client(info, s_client);
    size_t start = 0;
    int value_write = LENGTH_COMMAND;
    char *data = get_next_data_to_send(&client->data_send);
    int len = (data) ? strlen(data) : 0;

    while (w_value < len && w_value > 0) {
        if (len < LENGTH_COMMAND)
            value_write = len;
        w_value += write(s_client, data + start, value_write);
        len -= value_write;
        start += w_value;
    }
    free(data);
    client->status = (get_size_data_to_send(client->data_send)) ? WRITE : READ;
    if (w_value < 0 || client->isQuit) {
        remove_client(info, s_client);
        (client->isQuit) ? close(s_client) : 0;
    }
}

void free_data(zappy_data_t *data)
{
    free_teams(data->teams);
    free_trantorians(data->trants);
    free_map(data->map);
}

void close_server(server_t *info)
{
    client_t *temp = info->list_client;
    client_t *next = NULL;

    FD_ZERO(&info->rfds);
    FD_ZERO(&info->wfds);
    while (temp) {
        next = temp->next;
        free(temp->buff_read);
        free_data_send(temp->data_send);
        free(temp);
        temp = next;
    }
    free_data(&info->data);
    close(info->fd_server);
    exit(0);
}
