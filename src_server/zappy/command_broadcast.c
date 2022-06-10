/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_broadcast
*/

#include "server.h"

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
	int x_dest = gest_pos(src->tile->x, dest->tile->x, data->map->height);
	int y_dest = gest_pos(src->tile->y, dest->tile->y, data->map->width);
	float c_dir;
	
	if (x_dest == 0)
		return 0;
	c_dir = y_dest / x_dest;
	if (c_dir < 0)
		c_dir *= -1;
	printf("X: %f, Y: %f, dir: %f\n", x_dest, y_dest, c_dir);
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

int send_broadcast(trantorians_t *trant, int i, int j, zappy_data_t *data)
{
	trantorians_t *current = data->map->tiles[i][j]->trantorians;
	int dir;

	while (current != NULL) {
		dir = find_path(trant, current, data);
		dir = (dir + current->direction * 3) % 8 + 1;
		// current->client
		current = current->next;
	}
	return 0;
}

int broadcast(trantorians_t *trant, char **args, zappy_data_t *data)
{
	int width = data->map->width;
	int height = data->map->height;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			send_broadcast(trant, i, j, data);
		}
	}
	return 0;
}
