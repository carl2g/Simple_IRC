##
## EPITECH PROJECT, 2018
## IRC
## File description:
## MAKEFILE
##

MA	=	make -C

MACLEAN	=	make clean -C

MV	=	mv

RM	=	rm -rf

all:
	make server

server:
	$(MA) ./serverirc
	$(MV) ./serverirc/server .

clean:
	$(MACLEAN) ./serverirc/

fclean: clean
	$(RM) server

re: fclean all

.PHONY: all server clean fclean re