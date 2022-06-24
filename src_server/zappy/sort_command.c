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

static int append_action(trantorians_t *trant, char **args, int pos, zappy_data_t *data)
{
    action_t *curr = trant->action;
    action_t *new = malloc(sizeof(action_t));

    if (trant->nb_action >= 10) {
        trant->client->data_send = add_send(trant->client->data_send, "ko\n");
        return (-1);
    }
    new->action = MY_CMDS[pos].fct;
    new->time_left = set_timespec(MY_CMDS[pos].time, data->freq);
    new->args = args;
    new->next = NULL;
    trant->nb_action++;
    while (curr && curr->next)
        curr = curr->next;
    if (curr)
        curr->next = new;
    else {
        trant->action = new;
        (new->action == &incantation) ? incantation(trant->client, args, data)
        : 0;
    }

    return (0);
}

int sort_command(client_t *client, zappy_data_t *data, char *arg)
{
    char **args = my_str_to_word_array(arg);

    for (int pos = 0; pos != (sizeof(MY_CMDS) / sizeof(*MY_CMDS)); pos++) {
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd)) &&
            MY_CMDS[pos].gui && client->is_gui) {
            MY_CMDS[pos].fct(client, args, data);
            free_array(args);
            return (0);
        }
        if (!strncmp(arg, MY_CMDS[pos].cmd, strlen(MY_CMDS[pos].cmd)) &&
            !MY_CMDS[pos].gui && !client->is_gui) {
            append_action(client->trant, args, pos, data);
            return (0);
        }
    }
    if (client->is_gui)
        unknown_gui_command(client);
    free_array(args);
    client->data_send = add_send(client->data_send, "ko\n");
    return (1);
}

static void add_trantoriant(client_t *cli, server_t *info, char *cmd)
{
    team_t *team = get_team_by_name(cmd, info->data);
    char *line = NULL;

    if (!team || team->nb_player >= team->player_max) {
        if (team->nb_player >= team->player_max && added_in_egg(cli, info, team))
            return;
        cli->data_send = add_send(cli->data_send, (!team) ? "unknow team\n" :
        "team is already full please wait until a client disconnect " \
        "or fork\n");
    } else {
        cli->trant = create_add_trantoriant(cli, info->data, team->name);
        asprintf(&line, "%d\n", (team->player_max - team->nb_player));
        cli->data_send = add_send(cli->data_send, line);
        free(line);
        init_trantoriant(cli, info, team, false);
        new_player_connect(cli->trant);
        asprintf(&line, "%d %d\n", info->data->width, info->data->height);
        cli->data_send = add_send(cli->data_send, line);
        free(line);
    }
}

static void connect_gui(client_t *cli, zappy_data_t *data)
{
    cli->is_gui = true;
    gui_map_size(cli, NULL, data);
    gui_time_unit_request(cli, NULL, data);
    gui_map_content(cli, NULL, data);
    gui_teams_name(cli, NULL, data);
}

void handle_command(server_t *info, client_t *cli)
{
    char *value = NULL;
    value = read_to_buffer(cli->buff_read, '\n', LENGTH_COMMAND);
    if (!value || value[0] == '\n' || value[0] == 0) {
        free(value);
        return;
    }
    if (!strcasecmp(value, "gui") || !strcasecmp(value, "graphic")) {
        connect_gui(cli, info->data);
        free(value);
        return;
    }
    if (!cli->trant && !cli->is_gui && !cli->egg)
        add_trantoriant(cli, info, value);
    else if (!cli->egg)
        sort_command(cli, info->data, value);
    handle_command(info, cli);
    free(value);
}
