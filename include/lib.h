/*
** EPITECH PROJECT, 2022
** lib.h
** File description:
** lib
*/

#ifndef LIB_H_
    #define LIB_H_
    #define LENGTH 512

typedef struct buffer_s {
    char buffer[LENGTH];
    char *wronly;
    char *rdonly;
} buffer_t;

char *array_to_str(char **array);
char *array_to_str_separator(char **array, char separator);
char *clear_str(char *str);
int find_char_in_str(char c, char *to_find);
int count_char_in_str(char c, char *to_find);
void free_array(char **array);
int my_intlen(int nb);
char **my_str_to_word_array(char *str);
char **remove_part_of_array(char **array, int last_index);
char *remove_to_last_char(char *str, char to_find);
char **str_to_word_array_separator(char *str, char separator);
char *strcatdup(char *src, char *to_add, char *between);
int strlen_array(char **array);
int count_until_char(char *str, char c);
char *read_to_buffer(buffer_t *buff, char end_of_line, int length_max);
void add_to_write(buffer_t *buff, char *value, int length_max);
void init_buffer(buffer_t *buff, int length_command);
int len_array(char **array);
char *generate_uuid(void);
int modulo(int a, int b);

#endif /* !LIB_H_ */
