/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** server_communication
*/

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "client.h"

char *read_server(int socket)
{
    int valread;
    char *buff = calloc(1, 2048);

    if (!buff)
        return NULL;
    valread = read(socket, buff, 2048);
    if (valread <= 0) {
        free(buff);
        return "end";
    }
    buff[valread] = '\0';
    return buff;
}
