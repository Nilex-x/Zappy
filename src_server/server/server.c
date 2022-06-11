/*
** EPITECH PROJECT, 2022
** teams_serv.c
** File description:
** teams_serv
*/

#include "server.h"
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

server_t info;

void interrupt_sig(int sigint)
{
    if (sigint == SIGINT)
        close_server(&info);
}

void print_help(void)
{
    printf("USAGE:\t./myteams_server port\n\n\tport ");
    printf("is the port number on which the server socket listens\n\n");
}

int main(int argc, char **argv)
{
    signal(SIGINT, interrupt_sig);
    if ((argc == 2 && strcmp(argv[1], "-help") == 0)) {
        print_help();
        return (84);
    }
    handle_flags(&info, argc, argv);
    info.data = malloc(sizeof(zappy_data_t));
    if (!info.data)
        return (84);
    info.data->map = map_create(info.data->width, info.data->height);
    if (create_socket(&info) == -1)
        return (84);
    handler_connection(&info);
    close(info.fd_server);
    return (0);
}
