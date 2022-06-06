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
						src_server/server/manage_data_send.c \
						src_server/server/manage_flags.c\
						src_server/zappy/manage_team.c

OBJ_SERVER		=		$(SRC_SERVER:.c=.o)

CLIENT_NAME		=		zappy_ai

SRC_CLIENT		=		src_client/ia/main.py

CLIENT_LIB_PATH	=		src_client/client

HEADER_PATH		=		include

LIB_PATH		=		libs

CFLAGS			=		-W -Wall -Wextra -I$(HEADER_PATH)

LDFLAGS			=		-Llibs -lzappy -lmap

all: compil_lib compil_server compil_client

compil_lib:
	@make -C $(LIB_PATH)
	@make -C $(CLIENT_LIB_PATH)

compil_server: $(OBJ_SERVER)
	$(CC) -o $(SERVER_NAME) $(OBJ_SERVER) $(LDFLAGS)

compil_client:
	cp $(SRC_CLIENT) $(CLIENT_NAME)
	chmod +x $(CLIENT_NAME)

debug: CFLAGS += -g3
debug: compil_lib compil_server

clean:
	@make clean -C $(CLIENT_LIB_PATH)
	@make clean -C $(LIB_PATH)
	rm -f $(OBJ_SERV)

fclean:
	@make fclean -C $(LIB_PATH)
	@make fclean -C $(CLIENT_LIB_PATH)
	rm -f $(OBJ_SERV)
	rm -f $(SERVER_NAME)
	rm -f $(CLIENT_NAME)

re: fclean all

.PHONY: debug fclean clean re all


