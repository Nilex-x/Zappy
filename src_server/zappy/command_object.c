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

    while(strcmp(ressources[i], arg) != 0)
        i++;
    return i;
}

int pick_item(client_t *client, char **args, zappy_data_t *data)
{
    int object = get_obj(args[0]);

    (void) data;
    if (client->trant->tile->ressources[object] > 0) {
        client->trant->tile->ressources[object]--;
        client->trant->inventory[object]++;
        client->data_send = add_send(client->data_send, "ok\n");
        return 1;
    }
    client->data_send = add_send(client->data_send, "ko\n");
    return 0;
}

int drop_item(client_t *client, char **args, zappy_data_t *data)
{
    int object = get_obj(args[0]);

    (void) data;
    if (client->trant->inventory[object] > 0) {
        client->trant->inventory[object]--;
        client->trant->tile->ressources[object]++;
        client->trant->client->data_send = add_send(client->data_send, "ok\n");
        return 1;
    }
    client->data_send = add_send(client->data_send, "ko\n");
    return 0;
}
