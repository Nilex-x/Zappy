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
    #include <stdbool.h>
    #include "server.h"

    const char *world_ressources[7] = {"food", "linemate","deraumere","sibur","mendiane","phiras","thystame"};
    enum Inventory {
        FOOD,
        LINEMATE,
        DERAUMERE,
        SIBUR,
        MENDIANE,
        PHIRAS,
        THYSTAME
    };

    void display_inventory(client_t *client);
#endif