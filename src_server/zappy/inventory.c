/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#define _GNU_SOURCE
#include "inventory.h"

int display_inventory(trantorians_t *trant, char **args, zappy_data_t *data)
{
    (void) data;
    (void) args;

    trant->client->data_send = add_send(trant->client->data_send, "[");
    for (int i = 0; i < 7; i++) { 
        char *line = NULL;
        asprintf(&line, "%s %d", ressources[i], trant->inventory[i]);
        trant->client->data_send = add_send(trant->client->data_send, line);
        if(i+1 != 7)
        trant->client->data_send = add_send(trant->client->data_send, ", ");
            //trant->client->data_send = add_send(trant->client->data_send, ", ");
    }
    trant->client->data_send = add_send(trant->client->data_send, "]\n");
    return 0;
}