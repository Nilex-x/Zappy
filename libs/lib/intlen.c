/*
** EPITECH PROJECT, 2022
** intlen.c
** File description:
** intlen
*/

int my_intlen(int nb)
{
    int count = 0;

    while (nb > 0) {
        nb = nb / 10;
        count++;
    }
    return (count);
}
