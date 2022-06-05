/*
** EPITECH PROJECT, 2022
** teams_serv.c
** File description:
** teams_serv
*/

#include "server.h"
#include <signal.h>

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
    if ((argc == 2 && strcmp(argv[1], "-help") == 0) || argc != 2) {
        print_help();
        return (84);
    }
    info.port = atoi(argv[1]);
    if (info.port < 1024) {
        printf("0 to 1024 port number is not allowed to be used\n");
        return (84);
    }
    if (create_socket(&info) == -1)
        return (84);
    signal(SIGINT, interrupt_sig);
    handler_connection(&info);
    close(info.fd_server);
    return (0);
}
