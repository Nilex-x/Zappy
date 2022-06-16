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
        .cmd = "Inventory",
        .fct = &display_inventory,
        .time = 1
    },
    {
        .cmd = "Eject",
        .fct = &eject,
        .time = 7
    },
    {
        .cmd = "Forward",
        .fct = &forward,
        .time = 7
    },
    {
        .cmd = "Right",
        .fct = &right,
        .time = 7
    },
    {
        .cmd = "Left",
        .fct = &left,
        .time = 7
    },
    {
        .cmd = "Look",
        .fct = &look,
        .time = 7
    },
    {
        .cmd = "Fork",
        .fct = &fork_command,
        .time = 42
    },
    {
        .cmd = "Connect_nbr",
        .fct = &team_unused_slot
    },
    {
        .cmd = "Take",
        .fct = &pick_item,
        .time = 7
    },
    {
        .cmd = "Set",
        .fct = &drop_item,
        .time = 7
    },
    {
        .cmd = "Broadcast",
        .fct = &broadcast,
        .time = 7
    },
    {
        .cmd = "Incantation",
        .fct = &incantation,
        .time = 300
    },
    {
        .cmd = "msz",
        .fct = &gui_map_size
    },
    {
        .cmd = "bct",
        .fct = &gui_tile_content
    },
    {
        .cmd = "mct",
        .fct = &gui_map_content
    },
    {
        .cmd = "tna",
        .fct = &gui_teams_name
    },
    {
        .cmd = "ppo",
        .fct = &gui_player_pos
    },
    {
        .cmd = "plv",
        .fct = &gui_player_lvl
    },
    {
        .cmd = "pin",
        .fct = &gui_player_inventory
    },
    {
        .cmd = "sgt",
        .fct = &gui_time_unit_request
    },
    {
        .cmd = "sst",
        .fct = &gui_time_unit_modif
    }
};

static void append_action(trantorians_t *trant, char **args, int pos, zappy_data_t *data)
{
    action_t *curr = trant->action;
    action_t *new = malloc(sizeof(action_t));

    new->action = MY_CMDS[pos].fct;
    new->time_left = set_timespec(MY_CMDS[pos].time, data->freq);
    new->args = args;
    new->next = NULL;
    while (curr && curr->next)
        curr = curr->next;
    if (curr)
        curr->next = new;
    else if (new->action == &incantation) {
        incantation(trant->client, args, data);
        trant->action = new;
    } else
        trant->action = new;
}

int sort_command(client_t *client, zappy_data_t *data, char *arg)
{
    int cmd_size = sizeof(MY_CMDS) / sizeof(*MY_CMDS);
    char **args = my_str_to_word_array(arg);

    for (int pos = 0; pos != cmd_size; pos++) {
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd))) {
            (client->trant) ? append_action(client->trant, args
            , pos, data) : MY_CMDS[pos].fct(client, args, data);
            return (0);
        }
    }
    free_array(args);
    return (1);
}
