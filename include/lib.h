/*
** EPITECH PROJECT, 2022
** lib.h
** File description:
** lib
*/

#ifndef LIB_H_
    #define LIB_H_
    #define LENGHT 1024

typedef struct buffer_s {
    char buffer[LENGHT];
    char *wronly;
    char *rdonly;
} buffer_t;

/*
** @brief Change array of char by string
**
** @param array Array to change
** @return char *
*/
char *array_to_str(char **array);

/*
** @brief Change array of char by string with specific separator between index
**
** @param array Array to change
** @param separator Separator to add between
** @return char *
*/
char *array_to_str_separator(char **array, char separator);

/*
** @brief Remove \n of string
**
** @param str String to clean
** @return char*
*/
char *clear_str(char *str);

/*
** @brief Find a char in string
**
** @param c Char to find
** @param to_find String where find a char
** @return int
*/
int find_char_in_str(char c, char *to_find);

/*
** @brief Count char in strign
**
** @param c Char to count
** @param to_find String where count a char
** @return int
*/
int count_char_in_str(char c, char *to_find);

/*
** @brief Free a array
**
** @param array Array to free
*/
void free_array(char **array);

/*
** @brief Get length of number
**
** @param nb Number to count
** @return int
*/
int my_intlen(int nb);

/*
** @brief Change string to array
**
** @param str String to change
** @return char **
*/
char **my_str_to_word_array(char *str);

/*
** @brief Remove content of array
**
** @param array Array to remove part
** @param last_index Last index of array to remove
** @return char **
*/
char **remove_part_of_array(char **array, int last_index);

/*
** @brief Cut string until specific char
**
** @param str String to cut
** @param to_find Char to cut by him
** @return char *
*/
char *remove_to_last_char(char *str, char to_find);

/*
** @brief Change string to array with specific separator
**
** @param str String to change
** @param separator Separator of string
** @return char **
*/
char **str_to_word_array_separator(char *str, char separator);

/*
** @brief Concat and alloc two string
**
** @param src First string
** @param to_add Second string
** @param between Separator
** @return char *
*/
char *strcatdup(char *src, char *to_add, char *between);

/*
** @brief Get length of all iteration of  array
**
** @param array Array to get length
** @return int
*/
int strlen_array(char **array);

/*
** @brief Count string length until specific char
**
** @param str String to get length
** @param c Char to count until him
** @return int
*/
int count_until_char(char *str, char c);

/*
** @brief Read buffer circular
**
** @param buff Buffer struct
** @param end_of_line Char end of line
** @param length_max Length max of buffer
** @return char *
*/
char *read_to_buffer(buffer_t *buff, char end_of_line, int length_max);

/*
** @brief Add to write in buffer
**
** @param buff Buffer struct
** @param value String to add
** @param length_max Length max of buffer
*/
void add_to_write(buffer_t *buff, char *value, int length_max);

/*
** @brief Initialize buffer
**
** @param buff Buffer to initialize
** @param length_command Length max of buffer
*/
void init_buffer(buffer_t *buff, int length_command);

/*
** @brief Get length of array
**
** @param array Array to count
** @return int
*/
int len_array(char **array);

/*
** @brief Generate random uuid
**
** @return char*
*/
char *generate_uuid(void);

/*
** @brief Return module of two number
**
** @param a Number 1
** @param b Number 2
** @return int
*/
int modulo(int a, int b);

#endif /* !LIB_H_ */
