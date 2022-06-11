/*
** EPITECH PROJECT, 2022
** sort_command.c
** File description:
** sort_command
*/

#include "server.h"
#include <stdio.h>

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

void append_action(action_t **act, char **args, int pos)
{
    action_t *curr = *act;
    action_t *new = malloc(sizeof(action_t));

    new->action = MY_CMDS[pos].cmd;
    new->time_left = MY_CMDS[pos].time;
    new->args = args;
    new->next = NULL;
    while (curr && curr->next)
        curr = curr->next;
    if (curr)
        curr->next = new;
    else
        *act = new;
}

int sort_command(client_t *client, zappy_data_t *data, char *arg)
{
    int cmd_size = sizeof(MY_CMDS) / sizeof(*MY_CMDS);
    char **args = my_str_to_word_array(arg);

    for (int pos = 0; pos != cmd_size; pos++) {
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd))) {
            append_action(&client->trant->action, args, pos);
            return (0);
        }
    }
    return (1);
}
