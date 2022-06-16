/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** handle_look_command
*/

#include "server.h"
#include <stdio.h>

static char *look_right(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = -s; x <= s; x++) {
            new_x = modulo(trant->tile->x + s, map->width);
            new_y = modulo(trant->tile->y + x, map->height);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

static char *look_left(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x - s, map->width);
            new_y = modulo(trant->tile->y + x, map->height);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

static char *look_up(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = -s; x <= s; x++) {
            new_x = modulo(trant->tile->x + x, map->width);
            new_y = modulo(trant->tile->y - s, map->height);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

static char *look_down(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x + x, map->width);
            new_y = modulo(trant->tile->y + s, map->height);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

int look(client_t *client, char **arg, zappy_data_t *data)
{
    char *res = NULL;

    (void) arg;
    if (client->trant->direction == NORTH)
        res = look_up(data->map, client->trant);
    if (client->trant->direction == EAST)
        res = look_right(data->map, client->trant);
    if (client->trant->direction == SOUTH)
        res = look_down(data->map, client->trant);
    if (client->trant->direction == WEST)
        res = look_left(data->map, client->trant);
    client->data_send = add_send(client->data_send, res);
    free(res);
    return 0;
}
