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
        .time = 1,
        .gui = false
    },
    {
        .cmd = "Eject",
        .fct = &eject,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Forward",
        .fct = &forward,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Right",
        .fct = &right,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Left",
        .fct = &left,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Look",
        .fct = &look,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Fork",
        .fct = &fork_command,
        .time = 42,
        .gui = false
    },
    {
        .cmd = "Connect_nbr",
        .fct = &team_unused_slot,
        .gui = false
    },
    {
        .cmd = "Take",
        .fct = &pick_item,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Set",
        .fct = &drop_item,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Broadcast",
        .fct = &broadcast,
        .time = 7,
        .gui = false
    },
    {
        .cmd = "Incantation",
        .fct = &incantation,
        .time = 300,
        .gui = false
    },
    {
        .cmd = "msz",
        .fct = &gui_map_size,
        .gui = true
    },
    {
        .cmd = "bct",
        .fct = &gui_tile_content,
        .gui = true
    },
    {
        .cmd = "mct",
        .fct = &gui_map_content,
        .gui = true
    },
    {
        .cmd = "tna",
        .fct = &gui_teams_name,
        .gui = true
    },
    {
        .cmd = "ppo",
        .fct = &gui_player_pos,
        .gui = true
    },
    {
        .cmd = "plv",
        .fct = &gui_player_lvl,
        .gui = true
    },
    {
        .cmd = "pin",
        .fct = &gui_player_inventory,
        .gui = true
    },
    {
        .cmd = "sgt",
        .fct = &gui_time_unit_request,
        .gui = true
    },
    {
        .cmd = "sst",
        .fct = &gui_time_unit_modif,
        .gui = true
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
    char **args = my_str_to_word_array(clear_str(arg));

    for (int pos = 0; pos != (sizeof(MY_CMDS) / sizeof(*MY_CMDS)); pos++) {
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd)) &&
            MY_CMDS[pos].gui && client->is_gui) {
            MY_CMDS[pos].fct(client, args, data);
            free_array(args);
            return (0);
        }
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd)) &&
            !MY_CMDS[pos].gui && !client->is_gui) {
            printf("nice command [%s]\n", MY_CMDS[pos].cmd);
            append_action(client->trant, args, pos, data);
            free_array(args);
            return (0);
        }
    }
    free_array(args);
    client->data_send = add_send(client->data_send, "ko\n");
    return (1);
}
