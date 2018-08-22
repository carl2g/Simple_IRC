##
## EPITECH PROJECT, 2018
## IRC
## File description:
## makefile server
##

CC	=	gcc -g

RM	=	rm -rf

CFLAGS	+=	-Wall -Wextra -Werror -I./include -I./../commun

NAME	=	server

OBJS		=	$(SRCS:.c=.o)

SRCS	=	src/main.c 					\
			src/init_socket.c 			\
			src/main_loop.c 			\
			src/client_list.c 			\
			src/get_client_request.c 	\
			src/cmd_server_managment.c 	\
			src/nick_name.c 			\
			src/display_list.c 			\
			../commun/utils.c 			\
			../commun/utils2.c 			\
			../commun/utils3.c 			\
			src/chanel_list.c 			\
			src/wrap_chan_list.c 		\
			src/wrap_client_list.c 		\
			src/private_msg.c 			\
			src/join.c 					\
			src/utils_serv.c 			\
			src/add_client.c 			\
			src/part.c 					\
			src/quit.c 					\
			src/user_name.c 			\
			src/list_clients_in_chan.c

all: 		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: 	fclean all

.PHONY: all clean fclean re