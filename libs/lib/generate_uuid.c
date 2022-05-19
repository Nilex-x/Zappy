/*
** EPITECH PROJECT, 2022
** generate_uuid.c
** File description:
** generate_uuid
*/

#include <uuid/uuid.h>
#include <stdlib.h>

char *generate_uuid(void)
{
    uuid_t uid;
    char *uuid = NULL;

    uuid_generate(uid);
    uuid = malloc(sizeof(char) * 37);
    uuid_unparse(uid, uuid);
    return uuid;
}