/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#define _GNU_SOURCE
#include "inventory.h"

static int get_inventory_length(client_t *client)
{
    int length = 0;
    for (int i = 0; i < 7; i++) {
        char *line = NULL;
        asprintf(&line, "%s %d", ressources[i], client->trant->inventory[i]);
        length += strlen(line);
        if (i + 1 != 7)
            length += 2;
        free(line);
    }
    return (length);
}

int display_inventory(client_t *client, char **args, zappy_data_t *data)
{
    int length = get_inventory_length(client);
    char *new_line = malloc(length + 4);

    (void) data;
    (void) args;
    strcpy(new_line, "[");
    for (int i = 0; i < 7; i++) {
        char *line = NULL;
        asprintf(&line, "%s %d", ressources[i], client->trant->inventory[i]);
        strcat(new_line, line);
        if(i+1 != 7)
            strcat(new_line, ", ");
        free(line);
    }
    strcat(new_line, "]\n\0");
    client->data_send = add_send(client->data_send, new_line);
    free(new_line);
    printf("inventory = %s\n", client->data_send->data);
    return 0;
}