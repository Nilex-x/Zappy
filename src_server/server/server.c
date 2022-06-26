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

static void interrupt_sig(int sigint)
{
    if (sigint == SIGINT)
        close_server(&info);
}

static void print_help(void)
{
    printf("USAGE: ./zappy_server -p port -x width -y height -n name1 ");
    printf("name2 ... -c clientNb -f freq\n\tport ");
    printf("is the port number on which the server socket listens\n");
    printf("\twidth      is the width of the world\n");
    printf("\theight     is the height of the world\n");
    printf("\tnameX      is the name of the team X\n");
    printf("\tclientNb   is the number of authorized clients per team\n");
    printf("\tfreq       is the reciprocal of the time unit for execution ");
    printf("of actions\n");
}

int main(int argc, char **argv)
{
    signal(SIGINT, interrupt_sig);
    if ((argc == 2 && strcmp(argv[1], "-help") == 0)) {
        print_help();
        return (84);
    }
    init_data_struct(&info);
    handle_flags(&info, argc, argv);
    info.data->map = map_create(info.data->width, info.data->height);
    info.data->map->timeleft = set_timespec(20, info.data->freq);
    if (create_socket(&info) == -1)
        return (84);
    init_client(&info);
    handler_connection(&info);
    close(info.fd_server);
    return (0);
}
