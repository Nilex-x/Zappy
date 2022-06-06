/*
** EPITECH PROJECT, 2022
** client.c
** File description:
** client
*/

// #include "lib.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "client.h"

info_t *info;

int init_info(int socket)
{
    info = malloc(sizeof(info_t));
    if (!info)
        return -1;
    info->socket = socket;
    info->buff = NULL;
    info->read_write = READ;
    FD_SET(socket, &info->exceptfds);
    FD_SET(socket, &info->readfds);
    FD_ZERO(&info->writefds);
    return 0;
}

int create_client(char *ip, int port)
{
    int client_socket;
    int serv_len;
    struct sockaddr_in serv_addr;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (!client_socket)
        return -1;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) < 0)
        return -1;
    serv_len = sizeof(serv_addr);
    if (connect(client_socket, (struct sockaddr*)&serv_addr, serv_len) < 0)
        return -1;
    return (client_socket);
}

void clear_fd()
{
    FD_ZERO(&info->readfds);
    FD_ZERO(&info->writefds);
    FD_ZERO(&info->exceptfds);
    FD_SET(info->socket, &info->exceptfds);
    FD_SET(0, &info->readfds);
    if (info->read_write == READ) {
        FD_SET(info->socket, &info->readfds);
    } else {
        FD_SET(info->socket, &info->writefds);
    }
}

int client_select()
{
    int max = info->socket + 1;

    clear_fd();
    if (select(max, &info->readfds, &info->writefds, &info->exceptfds, NULL)) {
        if (FD_ISSET(info->socket, &info->exceptfds))
            return -1;
        if (FD_ISSET(info->socket, &info->readfds))
            return 1;
        if (FD_ISSET(info->socket, &info->writefds)) {
            write(info->socket, info->buff, strlen(info->buff));
            free(info->buff);
            info->read_write = READ;
            return 2;
        }
    }
    return 0;
}

int test(char *send) {
    info->buff = strdup(send);
    info->read_write = WRITE;
    return 0;
}
