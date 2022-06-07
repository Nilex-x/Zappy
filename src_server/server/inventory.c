/*
** EPITECH PROJECT, 2021
** undefined
** File description:
** inventory.c
*/

#include "inventory.h"

void display_inventory(trantorians_t *trant, char **args, zappy_data_t *data)
{
    (void) data;
    (void) args;

    printf("[");
    for (int i = 0; i < 8; i++) { 
        printf("%s %d", ressources[i], trant->inventory[i]);
        if(i+1 != 8)
            printf(", ");
    }
    printf("]\n");
}