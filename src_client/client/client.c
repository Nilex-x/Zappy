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

void write_to_serv(char *send, int socket)
{
    write(socket, send, strlen(send));
}
