##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

SRC			=		my_str_to_word_array.c \
					find_char_in_str.c \
					array_to_str.c \
					clear_str.c \
					remove_to_last_char.c \
					str_to_word_array_separator.c \
					strlen_array.c \
					intlen.c \
					free_array.c \
					remove_part_of_array.c \
					strcatdup.c \
					manage_buffer.c \
					modulo.c

OBJ 		=		$(SRC:.c=.o)

NAME_LIB	=		libzappy.a

INCLUDE_PATH	=	../../include

CFLAGS		=		-W -Wall -Wextra -I$(INCLUDE_PATH)

all: create_lib

create_lib: $(OBJ)
	@ar cr $(NAME_LIB) $(OBJ)
	@echo "Lib create"

clean:
	@rm -f $(OBJ)
	@echo "all .o is remove"

fclean: clean
	@rm -f $(NAME_LIB)
	@echo "Lib is remove"
