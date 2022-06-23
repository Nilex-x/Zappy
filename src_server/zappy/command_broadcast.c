/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_broadcast
*/

#include "server.h"
#include <stdio.h>

static int get_pos(int a, int b, int map_size)
{
    int dist = b - a;

    if (abs(dist) <= (map_size - abs(dist)))
        return dist;
    if (a < b)
        return (-(map_size - abs(dist)));
    return (map_size - abs(dist));
}

static int check_sides(int x_dest, int y_dest, float c_dir)
{
    if (y_dest > 0) {
        if (c_dir > 1)
            return 1;
        if (x_dest > 0)
            return 3;
        if (x_dest < 0)
            return 7;
    }
    if (y_dest < 0) {
        if (c_dir > 1)
            return 5;
        if (x_dest > 0)
            return 3;
        if (x_dest < 0)
            return 7;
    }
    return 0;
}

static int find_path(trantorians_t *src, trantorians_t *dest, zappy_data_t *data)
{
    int x_dest = get_pos(src->tile->x, dest->tile->x, data->map->width);
    int y_dest = get_pos(src->tile->y, dest->tile->y, data->map->height);
    float c_dir;

    if (x_dest == 0)
        return (y_dest > 0) ? 5 : (y_dest == 0) ? 0 : 1;
    if (y_dest == 0)
        return (x_dest > 0) ? 3 : (x_dest == 0) ? 0 : 7;
    c_dir = y_dest / x_dest;
    if (c_dir < 0)
        c_dir *= -1;
    if (x_dest > 0 && (y_dest == x_dest))
        return 2;
    if (x_dest < 0 && (y_dest == x_dest))
        return 6;
    if (x_dest > 0 && (abs(y_dest) == x_dest))
        return 4;
    if (x_dest < 0 && (y_dest == abs(x_dest)))
        return 8;
    return (check_sides(x_dest, y_dest, c_dir));
}

int broadcast(client_t *client, char **args, zappy_data_t *data)
{
    trantorians_t *current = data->trants;
    char *buff = 0;
    int dir = 0;
    int cdir = 0;

    broadcast_message(current, args);
    while (current != NULL) {
        if (current->client->socket != client->socket) {
            dir = find_path(client->trant, current, data);
            cdir = current->direction;
            printf("DIR: %d\n", dir);
            if (dir)
                dir = (dir + cdir * 2) % (8 + (dir + cdir * 2 == 8));
            asprintf(&buff, "message %d, %s\n", dir, args[1]);
            current->client->data_send = add_send(current->client->data_send, buff);
            free(buff);
        }
        current = current->next;
    }
    client->data_send = add_send(client->data_send, "ok\n");
    return 0;
}
