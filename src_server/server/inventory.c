/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#include "server.h"
#include "inventory.h"

void display_inventory(client_t *client)
{
    dprintf(client->socket, "[");
    for (int i = 0; i < 8; i++) { 
        dprintf(client->socket, "%s %d", world_ressources[i], client->inventory[i]);
        if(i+1 != 8)
            dprintf(client->socket, ", ");
    }
    dprintf(client->socket, "]\n");
}