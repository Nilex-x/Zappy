/*
** EPITECH PROJECT, 2022
** Zappy
** File description:
** command_object
*/

#include "server.h"
#include <stdio.h>

static int notif_inventory(client_t *client, server_t *info)
{
    char *line = NULL;

    asprintf(&line, "pin %d %ld %ld %d %d %d %d %d %d %d\n", client->socket,
    client->trant->tile->x, client->trant->tile->y,
    client->trant->inventory[0], client->trant->inventory[1],
    client->trant->inventory[2], client->trant->inventory[3],
    client->trant->inventory[4], client->trant->inventory[5],
    client->trant->inventory[6]);
    for (client_t *c = info->list_client; c; c = c->next) {
        if (c->is_gui)
            c->data_send = add_send(c->data_send, line);
    }
    free(line);
    return (0);
}

static int get_obj(char *arg)
{
    int i = 0;

    if (!arg)
        return i;
    while (i < 7 && (strncmp(ressources[i], arg, strlen(ressources[i])) != 0))
        i++;
    return i;
}

int pick_item(client_t *client, char **args, zappy_data_t *data)
{
    int object = 0;

    (void) data;
    if (len_array(args) != 2) {
        client->data_send = add_send(client->data_send, "ko\n");
        return 0;
    }
    object = get_obj(args[1]);
    if (client->trant->tile->ressources[object] > 0) {
        client->trant->tile->ressources[object]--;
        client->trant->inventory[object]++;
        client->data_send = add_send(client->data_send, "ok\n");
        ressource_collecting(client->trant, object);
        notif_inventory(client, data->server);
        return 1;
    }
    client->data_send = add_send(client->data_send, "ko\n");
    return 0;
}

int drop_item(client_t *client, char **args, zappy_data_t *data)
{
    int object = 0;

    (void) data;
    if (len_array(args) != 2) {
        client->data_send = add_send(client->data_send, "ko\n");
        return 0;
    }
    object = get_obj(args[1]);
    if (client->trant->inventory[object] > 0) {
        client->trant->inventory[object]--;
        client->trant->tile->ressources[object]++;
        client->trant->client->data_send = add_send(client->data_send, "ok\n");
        ressource_dropping(client->trant, object, data);
        notif_inventory(client, data->server);
        return 1;
    }
    client->data_send = add_send(client->data_send, "ko\n");
    return 0;
}
