/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.h
*/

#ifndef INVENTORY_H_
    #define INVENTORY_H_
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <stdlib.h>
    #include "zappy.h"
    #include "server.h"

extern const char *ressources[7];

enum Inventory {
    FOOD,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME
};

/*
** @brief display inventory to client
**
** @param client Client who do command
** @param args Arguments of commands
** @param data Data struct server
** @return int
*/
int display_inventory(client_t *client, char **args, zappy_data_t *data);
#endif