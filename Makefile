##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

CC				=		gcc

SERVER_NAME		=		zappy_server

SRC_SERVER		=		src_server/server/server.c \
						src_server/server/handle_client.c \
						src_server/server/handle_communication.c \
						src_server/server/manage_server.c \
						src_server/server/manage_init.c \
						src_server/server/manage_data_send.c

OBJ_SERVER		=		$(SRC_SERVER:.c=.o)

CLIENT_NAME		=		zappy_ai

SRC_CLIENT		=		src_client/ia/main.py

CLIENT_LIB_PATH	=		src_client/client

HEADER_PATH		=		include

LIB_PATH		=		libs

NAME_LIB		=		zappy

CFLAGS			=		-W -Wall -Wextra -I$(HEADER_PATH) -L$(LIB_PATH) -l$(NAME_LIB)

all: compil_lib compil_server compil_client

compil_lib:
	@make -C $(LIB_PATH)
	@make -C $(CLIENT_LIB_PATH)

compil_server: $(OBJ_SERVER)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) -I$(HEADER_PATH) -L$(LIB_PATH) -l$(NAME_LIB)

compil_client:
	cp $(SRC_CLIENT) $(CLIENT_NAME)
	chmod +x $(CLIENT_NAME)

debug: compil_lib debug_server debug_client

debug_server: $(OBJ_SERVER)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) -I$(HEADER_PATH) -L$(LIB_PATH) -l$(NAME_LIB) -g3

debug_client: $(OBJ_CLIENT)
	$(CC) -o $(CLIENT_NAME) $(OBJ_CLIENT) -I$(HEADER_PATH) -L$(LIB_PATH) -l$(NAME_LIB) -g3

clean:
	@make clean -C $(CLIENT_LIB_PATH)
	@make clean -C $(LIB_PATH)
	rm -f $(OBJ_SERV)
	rm -f $(OBJ_CLIENT)

fclean:
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(CLIENT_LIB_PATH)
	rm -f $(OBJ_SERV)
	rm -f $(OBJ_CLIENT)
	rm -f $(SERV_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all

.PHONY: debug fclean clean re all


