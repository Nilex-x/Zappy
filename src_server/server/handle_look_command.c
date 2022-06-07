/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** handle_look_command
*/

#include "server.h"

char *look_up(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = -s; x <= s; x++) {
            new_x = modulo(trant->tile->x + s, map->height);
            new_y = modulo(trant->tile->y + x, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

char *look_down(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x - s, map->height);
            new_y = modulo(trant->tile->y + x, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

char *look_left(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x + x, map->height);
            new_y = modulo(trant->tile->y - s, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

char *look_right(map_t *map, trantorians_t *trant)
{
    char *line = strdup("[");
    char *res = NULL;
    int new_x = trant->tile->x;
    int new_y = trant->tile->y;

    for (int s = 0; s <= trant->lvl; s++)
        for (int x = s; x >= -s; x--) {
            new_x = modulo(trant->tile->x + x, map->height);
            new_y = modulo(trant->tile->y + s, map->width);
            res = get_items_on_tile(map, new_x, new_y);
            (strlen(line) > 1) ? (strlen(res) > 1) ? (asprintf(&line, "%s, %s"
            , line, res)) : (asprintf(&line, "%s,", line)) : (asprintf(&line
            , "%s%s", line, res));
            free(res);
        }
    asprintf(&line, "%s]", line);
    return line;
}

char *look(trantorians_t *trant, char **arg, zappy_data_t *data)
{
    (void) arg;
    if (trant->direction == NORTH)
        return look_up(data->map, trant);
    if (trant->direction == EAST)
        return look_right(data->map, trant);
    if (trant->direction == SOUTH)
        return look_down(data->map, trant);
    return look_left(data->map, trant);
}
