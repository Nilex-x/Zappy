/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "server.h"

int test(client_t *client, zappy_data_t *data, char *args)
{
    printf("ayaoo\n");
}

static const cmd_t MY_CMDS[] = {
    {
        .cmd = "inventory",
        .fct = &display_inventory
    },
    {
        .cmd = "test",
        .fct = &test
    }
};

int sort_command(client_t *client, zappy_data_t *data, char *arg)
{
    int cmd_size = sizeof(MY_CMDS) / sizeof(*MY_CMDS);

    for (int pos = 0; pos != cmd_size; pos++) {
        printf("toto\n");
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd))) {
            MY_CMDS[pos].fct(client, data, arg);
            return (0);
        }
    }
    return (1);
}
