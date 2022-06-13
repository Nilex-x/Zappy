/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#define _GNU_SOURCE
#include "inventory.h"

int display_inventory(client_t *client, char **args, zappy_data_t *data)
{
    (void) data;
    (void) args;

    client->data_send = add_send(client->data_send, "[");
    for (int i = 0; i < 7; i++) {
        char *line = NULL;
        asprintf(&line, "%s %d", ressources[i], client->trant->inventory[i]);
        client->data_send = add_send(client->data_send, line);
        if(i+1 != 7)
            client->data_send = add_send(client->data_send, ", ");
        free(line);
    }
    client->data_send = add_send(client->data_send, "]\n");
    printf("inventory = %s\n", client->data_send->data);
    return 0;
}