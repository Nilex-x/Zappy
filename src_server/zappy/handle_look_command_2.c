/*
** EPITECH PROJECT, 2022
** handle_look_command_2.c
** File description:
** handle_look_command_2
*/

#include "zappy.h"
#include "lib.h"
#include "map_handler.h"
#include <stdlib.h>
#include <string.h>

char *get_content(int new_x, int new_y, map_t *map, char *line)
{
    char *res = NULL;
    char *ret = NULL;

    res = get_items_on_tile(map, new_x, new_y);
    if (strlen(line) > 1) {
        if (strlen(res) > 1) {
            ret = strcatdup(line, res, ", ");
        } else {
            ret = strcatdup(line, ",", "");
        }
    } else {
        ret = strcatdup(line, res, "");
    }
    free(res);
    return (ret);
}