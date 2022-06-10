/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_broadcast
*/

#include "server.h"
#include <stdio.h>

int get_pos(int a, int b, int map_size)
{
    int dist = b - a;

    if (abs(dist) <= (map_size - abs(dist)))
        return dist;
    if (a < b)
        return (-(map_size - abs(dist)));
    return (map_size - abs(dist));
}

int find_path(trantorians_t *src, trantorians_t *dest, zappy_data_t *data)
{
    int x_dest = get_pos(src->tile->x, dest->tile->x, data->map->width);
    int y_dest = get_pos(src->tile->y, dest->tile->y, data->map->height);
    float c_dir;
    
    if (x_dest == 0)
        return 0;
    c_dir = y_dest / x_dest;
    if (c_dir < 0)
        c_dir *= -1;
    if (x_dest > 0 && (y_dest == x_dest))
        return 6;
    if (x_dest < 0 && (y_dest == x_dest))
        return 2;
    if (x_dest > 0 && (x_dest == y_dest))
        return 8;
    if (x_dest < 0 && (y_dest == x_dest))
        return 4;
    if (y_dest > 0) {
        if (c_dir > 1)
            return 5;
        if (x_dest > 0 && c_dir < 1)
            return 7;
        if (x_dest < 0 && c_dir < 1)
            return 3;
    }
    if (y_dest < 0) {
        if (c_dir > 1)
            return 1;
        if (x_dest > 0 && c_dir < 1)
            return 7;
        if (x_dest < 0 && c_dir < 1)
            return 3;
    }
    return 0;
}

int send_broadcast(trantorians_t *trant, tile_t *tile, zappy_data_t *data, char *msg)
{
    trantorians_t *current = tile->trantorians;
    char buff[512];
    int dir;

    while (current != NULL) {
        dir = find_path(trant, current, data);
        if (dir)
            dir = (dir + current->direction * 3) % 8 + 1;
        sprintf(buff, "Received [%s] from [%d].\n", msg, dir);
        current->client->data_send = add_send(current->client->data_send, buff);
        current = current->next;
    }
    return 0;
}

int broadcast(trantorians_t *trant, char **args, zappy_data_t *data)
{
    int width = data->map->width;
    int height = data->map->height;

    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
            send_broadcast(trant, data->map->tiles[i][j], data, args[0]);
    return 0;
}
