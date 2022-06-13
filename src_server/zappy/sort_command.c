/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "server.h"
#include <stdio.h>

int test(client_t *client, char **args, zappy_data_t *data)
{
    printf("ayaoo\n");
    return 0;
}

static const cmd_t MY_CMDS[] = {
    {
        .cmd = "Inventory",
        .fct = &display_inventory
    },
    {
        .cmd = "test",
        .fct = &test
    },
    {
        .cmd = "Eject",
        .fct = &eject
    },
    {
        .cmd = "Forward",
        .fct = &forward
    },
    {
        .cmd = "Right",
        .fct = &right
    },
    {
        .cmd = "Left",
        .fct = &left
    }
};

int sort_command(client_t *client, zappy_data_t *data, char *arg)
{
    int cmd_size = sizeof(MY_CMDS) / sizeof(*MY_CMDS);
    char **args = my_str_to_word_array(arg);

    for (int pos = 0; pos != cmd_size; pos++) {
        // printf("toto\n");
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd))) {
            MY_CMDS[pos].fct(client, args, data);
            free_array(args);
            return (0);
        }
    }
    free_array(args);
    return (1);
}
