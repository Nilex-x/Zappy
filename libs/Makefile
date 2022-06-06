##
## EPITECH PROJECT, 2022
## Makefile
## File description:
## Makefile
##

LIB_PATH	=	lib/

MAP_PATH	=	map_handler/

MAP_NAME	=	libmap.a

LIB_NAME	=	libzappy.a

all: compil_lib compil_map

compil_lib: compil_map
	@make -C $(LIB_PATH)
	mv $(LIB_PATH)$(LIB_NAME) .

compil_map:
	@make -C $(MAP_PATH)
	mv $(MAP_PATH)/$(MAP_NAME) .

clean:
	@make clean -C $(LIB_PATH)

fclean:
	@make fclean -C $(LIB_PATH)
	@make fclean -C map_handler/
	@rm -f $(LIB_NAME)
	@rm -f libmap.a


re: fclean all
