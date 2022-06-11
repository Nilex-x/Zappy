/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_object
*/

#include "server.h"

int get_obj(char *arg)
{
	int i = 0;

	while(strcasecmp(ressources[i], arg) != 0)
		i++;
	return i;
}

int pick_item(trantorians_t *trant, char **args, zappy_data_t *data)
{
	int object = get_obj(args[1]);

	if (trant->tile->ressources[object] > 0) {
		trant->tile->ressources[object]--;
		trant->inventory[object]++;
		trant->client->data_send = add_send(trant->client->data_send, "ok\n");
		return 1;
	}
	trant->client->data_send = add_send(trant->client->data_send, "ko\n");
	return 0;
}

int drop_item(trantorians_t *trant, char **args, zappy_data_t *data)
{
	int object = get_obj(args[1]);

	if (trant->inventory[object] > 0) {
		trant->inventory[object]--;
		trant->tile->ressources[object]++;
		trant->client->data_send = add_send(trant->client->data_send, "ok\n");
		return 1;
	}
	trant->client->data_send = add_send(trant->client->data_send, "ko\n");
	return 0;
}
