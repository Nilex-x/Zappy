/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** gui_commands_1
*/

#include "server.h"
#include <stdio.h>

int gui_map_size(client_t *client, char **args, zappy_data_t *data)
{
    char *buff = NULL;

    (void) args;
    asprintf(&buff, "msz %d %d\n", data->width, data->height);
    client->data_send = add_send(client->data_send, buff);
    free(buff);
    return 0;
}

char *get_tile_content(int x, int y, zappy_data_t *data)
{
    char *buff = NULL;
    int *r = data->map->tiles[y][x]->ressources;

    asprintf(&buff, "bct %d %d %d %d %d %d %d %d %d\n"
    , x, y, r[0], r[1], r[2], r[3], r[4], r[5], r[6]);
    return buff;
}

int gui_tile_content(client_t *client, char **args, zappy_data_t *data)
{
    char *buff = NULL;

    printf("len: %d\n", len_array(args));
    if (len_array(args) != 3) {
        client->data_send = add_send(client->data_send, "ko\n");
        return 0;
    }
    buff = get_tile_content(atoi(args[1]), atoi(args[2]), data);
    client->data_send = add_send(client->data_send, buff);
    free(buff);
    return 0;
}

int gui_map_content(client_t *client, char **args, zappy_data_t *data)
{
    int width = data->map->width;
    int height = data->map->height;
    char *buff = NULL;

    (void) args;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            buff = get_tile_content(j, i, data);
            client->data_send = add_send(client->data_send, buff);
            free(buff);
        }
    }
    return 0;
}

int gui_teams_name(client_t *client, char **args, zappy_data_t *data)
{
    char *buff = NULL;
    team_t *current = data->teams;

    (void) args;
    while (current != NULL) {
        asprintf(&buff, "tna %s\n", current->name);
        client->data_send = add_send(client->data_send, buff);
        free(buff);
        current = current->next;
    }
    return 0;
}
