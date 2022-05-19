/*
** EPITECH PROJECT, 2022
** find_char_to_str.c
** File description:
** find_char_in_str
*/

int find_char_in_str(char c, char *to_find)
{
    if (!to_find)
        return (0);
    for (int i = 0; to_find[i]; i++) {
        if (to_find[i] == c)
            return (1);
    }
    return (0);
}

int count_char_in_str(char c, char *to_find)
{
    int count = 0;

    for (int i = 0; to_find[i] != '\0'; i++) {
        if (to_find[i] == c)
            count++;
    }
    return (count);
}

int count_until_char(char *str, char c)
{
    int count = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return (count);
        count++;
    }
    return (-1);
}
