/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#define _GNU_SOURCE
#include "inventory.h"

int display_inventory(client_t *client, zappy_data_t *data, char *args)
{
    (void) data;
    (void) args;

    client->data_send = add_send(client->data_send, "[");
    for (int i = 0; i < 7; i++) { 
        char *line = NULL;
        asprintf(&line, "%s %d", ressources[i], client->trant->inventory[i]);
        //client->data_send = add_send(client->data_send, line);
        if(i+1 != 7)
            strcat(line, ", ");
            //client->data_send = add_send(client->data_send, ", ");
        client->data_send = add_send(client->data_send, line);
    }
    client->data_send = add_send(client->data_send, "]\n");
    printf("%s\n", client->data_send->data);
    return 0;
}