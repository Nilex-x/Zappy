##
## EPITECH PROJECT, 2022
## myTeams_collaborate
## File description:
## Makefile
##

NAME = libmap.a

SRC = $(shell find -name '*.c')

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -I../../include

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp map_handler.h ../../include/

all:	$(NAME) fclean

clean:
	rm -f *~

fclean:		clean
	rm -f $(OBJ)

re:		fclean all