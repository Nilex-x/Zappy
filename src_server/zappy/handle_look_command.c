/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** handle_look_command
*/

#include "server.h"
#include <stdio.h>

static int look_up(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++) {
        for (int x = -s; x <= s; x++) {
            new_x = modulo(trant->tile->x + s, map->height);
            new_y = modulo(trant->tile->y + x, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    }
    asprintf(&line, "%s]", line);
    trant->client->data_send = add_send(trant->client->data_send, line);
    free(line);
    return (0);
}

static int look_down(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++) {
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x - s, map->height);
            new_y = modulo(trant->tile->y + x, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
        free(res);
    }
    asprintf(&line, "%s]", line);
    trant->client->data_send = add_send(trant->client->data_send, line);
    free(line);
    return (0);
}

static int look_left(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++) {
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x + x, map->height);
            new_y = modulo(trant->tile->y - s, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    }
    asprintf(&line, "%s]", line);
    trant->client->data_send = add_send(trant->client->data_send, line);
    free(line);
    return (0);
}

static int look_right(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++) {
        for (int x = -s; x <= s; x++) {
            new_x = modulo(trant->tile->x + x, map->height);
            new_y = modulo(trant->tile->y + s, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    }
    asprintf(&line, "%s]", line);
    trant->client->data_send = add_send(trant->client->data_send, line);
    free(line);
    return (0);
}

int look(client_t *client, char **arg, zappy_data_t *data)
{
    (void) arg;
    if (client->trant->direction == NORTH)
        look_up(data->map, client->trant);
    if (client->trant->direction == EAST)
       look_right(data->map, client->trant);
    if (client->trant->direction == SOUTH)
       look_down(data->map, client->trant);
    if (client->trant->direction == WEST)
       look_left(data->map, client->trant);
    return 0;
}
