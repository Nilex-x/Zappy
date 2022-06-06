##
## EPITECH PROJECT, 2022
## Zappy
## File description:
## Makefile
##

SRC_LIB	=		client.c \
				server_communication.c

OBJ_CLIENT		=		client.o \
				server_communication.o

LIB_NAME		=		clientLib.so

HEADER_PATH		=		../../include

all: compil_client_lib

compil_client_lib:
	$(CC) -g -fPIC $(SRC_LIB) -shared -o $(LIB_NAME) -I$(HEADER_PATH)

clean:
	@rm -f $(OBJ_CLIENT)

fclean:
	@rm -f $(OBJ_CLIENT)
	@rm -f $(LIB_NAME)


re: fclean all