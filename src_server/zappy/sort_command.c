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
