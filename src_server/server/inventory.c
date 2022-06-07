/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#include "inventory.h"

int display_inventory(trantorians_t *trant, char **args, zappy_data_t *data)
{
    (void) data;
    (void) args;
    printf("trant1 %d\n", trant->lvl);
    fflush(stdout);
    return 1;
    printf("trant2 %d\n", trant->inventory[0]);
    fflush(stdout);

    printf("[");
    for (int i = 0; i < 7; i++) { 
        printf("%s %d", ressources[i], trant->inventory[i]);
        if(i+1 != 7)
            printf(", ");
    }
    printf("]\n");
    return 0;
}