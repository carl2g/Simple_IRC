/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#ifndef _SERVER_HPP
	# define _SERVER_HPP

# include <sys/select.h>
# include "../commun/commun.h"

enum {
	FALSE,
	TRUE
};

# define HELP		"USAGE:\t./server port"
# define NICK		"NICK"
# define USER		"USER"
# define LIST_ALL_CHAN	"LIST"
# define JOIN		"JOIN"
# define PART		"PART"
# define LIST_ALL_USERS	"USERS"
# define NAMES		"NAMES"
# define PRIVATE_MSG	"PRIVMSG"
# define SEND_FILE	"SENDFILE"
# define ACCEPT_FILE	"ACCFILE"
# define SWITCH_CHAN	"SWITCH"
# define QUIT		"QUIT"
# define READ_SIZE	512
# define IP_LEN		24

# define INFO_USERS		"Member connected to server:"
# define INFO_CHANS		"Chanels available on the server:"
# define INFO_CHAN_USERS	"Users curently connected to chan %s:\r\n"
# define DEFAULT_NAME		"unknown"
# define END_LIST		"end list"

# define CONNECT_OK		"001 :Welcome to the CAlexServ"
# define NO_SUCH_NICK		"401 :No user found with this nickname"
# define NO_SUCH_CHAN		"403 :No such chan founed"
# define NO_RECEP		"411 :Unknown reciver"
# define NO_TEXT_TO_SEND	"412 :No text to send"
# define UNKNOW_CMD		"421 :unknown cmd"
# define NAMES_LIST		"353"
# define BAD_NICK		"432 :Use alphnum characters"
# define FILEERR		"424"
# define NO_NICK_SET		"431 :No nickname set"
# define LIST_OK		"322"
# define NICK_USED		"433 :Nickname alrady used"
# define RPL_L_START		"321 :Listing start"
# define RPL_L_END		"323 :Listing end"
# define TO_MANY_PARAM		"461 :To many parameters"
# define DEFAULT_QUIT_MSG 	"Byebye!!!"

extern int exit_sig;

typedef struct			chan_wrapper_s {
	struct chanel_list_s	*chan;
	struct chan_wrapper_s	*next;
	struct chan_wrapper_s	*prev;
}				chan_wrapper_t;

typedef struct			client_list_s {
	int			fd;
	char			*user_name;
	char			*nick_name;
	chan_wrapper_t		*wrap_chan_h;
	struct	client_list_s	*next;
}				client_list_t;

typedef struct			client_wrapper_s {
	client_list_t		*client;
	struct client_wrapper_s	*next;
	struct client_wrapper_s	*prev;
}				client_wrapper_t;

typedef struct			chanel_list_s {
	const char		*chan_name;
	client_wrapper_t	*h_client_wrap;
	struct chanel_list_s	*next;
}				chanel_list_t;

typedef struct		circular_buff_s {
	char		buff[READ_SIZE];
	int		head;
}			circ_buff_t;

typedef struct		control_struct_s {
	client_list_t	*head_client;
	chanel_list_t	*head_chan;
	circ_buff_t	circ_buff;
	fd_set		readfds;
	fd_set		writefds;
	int		fd_max;
	int		serv_fd;
	char		*ip;
}			control_struct_t;

typedef struct		data_struct_s {
	client_list_t	**client;
	char		**args;
	char		**cmd_args;
	char		*cmd;
}			data_struct_t;

typedef void (*ptr)(control_struct_t *, data_struct_t *);

client_list_t		*add_client(control_struct_t *manager, int fd);
client_list_t		*find_client(client_list_t *client,
			const char *nick_name);
chanel_list_t		*find_chan(const char *chan_name,
			control_struct_t *manager);
client_wrapper_t	*rm_client_wrap(client_wrapper_t *w,
			client_wrapper_t **head);
client_wrapper_t	*find_client_in_chan(chanel_list_t *chan,
			client_list_t *client);
chan_wrapper_t		*pop_chan_wrap(chan_wrapper_t *w,
			chan_wrapper_t **head);
chan_wrapper_t		*find_chan_w(chan_wrapper_t *chan,
			const char *chan_name);
client_list_t		*new_client(int fd);
int			init_socket(int port, control_struct_t *m);
char			*my_charcat(char *s1, char c);
char			*my_strcat(char *s1, const char *s2);
char			*epur_str(char *str, const char *epur);
char			triger_send_to_chan(chan_wrapper_t *w_chan,
			data_struct_t *data,
			const char *msg, const char *ip);
void			add_client_to_chan(control_struct_t *manager,
			const char *chan_name, client_list_t *client);
void			main_loop(control_struct_t *manager);
void			print_format(data_struct_t *data, const char *ip,
			const char *msg);
void			clean_client_list(client_list_t *head);
void			read_form_client(control_struct_t *manager);
void			remove_client_from_list(control_struct_t *manager,
			client_list_t **to_remove);
void			init_nickname(control_struct_t *manager,
			data_struct_t *data);
void			free_arr(char **arr);
char			send_to_chan(data_struct_t *data, const char *msg,
			const char *chan_name, const char *ip);
void			clean_chan_wrap_list(chan_wrapper_t *chan_wrap,
			client_list_t *client);
void			add_wrap_chan(client_list_t *client,
			chanel_list_t *add_chan);
void			remove_all_chan(chanel_list_t *chan);
void			add_wrap_client(chanel_list_t *chan,
			client_list_t *client);
void			print_info_chan(control_struct_t *manager);
int			my_strlen(const char *s);
void			clean_client_wrap_list(client_wrapper_t *wrap);
void			print_prv_msg(data_struct_t *data,
			client_list_t *client, const char *msg,
			const char *ip);
void			pop_client_wrap(control_struct_t *manager,
			const char *chan_name, client_list_t *client);
void			send_to_all_chans(chan_wrapper_t *w_chan,
			data_struct_t *data,
			const char *msg, const char *ip);
void 			print_format_prv_msg(data_struct_t *data,
			const char *ip, const char *msg, const char *reciver);
void			leave_chan(control_struct_t *manager,
			data_struct_t *data);
void			join_chan(control_struct_t *manager,
			data_struct_t *data);
void			list_all_users(control_struct_t *manager,
			data_struct_t *data);
void			list_all_chan(control_struct_t *manager,
			data_struct_t *data);
void			list_client_in_chan(control_struct_t *manager,
			data_struct_t *data);
void			list_chan_with_string(control_struct_t *manager,
			data_struct_t *data);
void			send_mesg(control_struct_t *manager,
			data_struct_t *data);
void			priv_mesg(control_struct_t *manager,
			data_struct_t *data);
void			switch_chan(control_struct_t *manager,
			data_struct_t *data);
void			client_quit(control_struct_t *manager,
			data_struct_t *data);
void			user_name(control_struct_t *manager,
			data_struct_t *data);
void			print_all_user_in_chan(client_list_t *c,
			chanel_list_t *h);

typedef struct	func_tab_s {
	char	*cmd;
	ptr	func;
}		func_tab_t;

static const func_tab_t func_tab[] = {
	{NICK,			init_nickname},
	{USER,			user_name},
	{LIST_ALL_CHAN,		list_all_chan},
	{JOIN,			join_chan},
	{PART,			leave_chan},
	{LIST_ALL_USERS,	list_all_users},
	{NAMES,			list_client_in_chan},
	{PRIVATE_MSG,		priv_mesg},
	{SWITCH_CHAN,		switch_chan},
	{QUIT,			client_quit},
	{NULL,			send_mesg}
};

#endif /* _SERVER_HPP */