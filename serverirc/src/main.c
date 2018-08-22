/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include "server.h"

int exit_sig = 0;

static int help(int val)
{
	printf("%s\n", HELP);
	return (val);
}

static void sig_handler(int signal)
{
	if (signal == SIGINT)
		exit_sig = 1;
}

static void init_manager_struct(control_struct_t *manager)
{
	manager->head_client = NULL;
	manager->head_chan = NULL;
	manager->fd_max = 3;
	bzero(&manager->circ_buff.buff, sizeof(manager->circ_buff.buff));
	manager->circ_buff.head = 0;
}

static int getnbr(const char *nb)
{
	int res = 0;

	if (nb == NULL)
		return (-1);
	for (int i = 0; nb[i] != '\0'; ++i) {
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			return (-1);
		res = res * 10 + (nb[i] - 48);
	}
	return (res);
}

int main(int ac, const char * const * av)
{
	int port = getnbr(av[1]);
	struct sigaction act;
	control_struct_t manager;

	init_manager_struct(&manager);
	bzero(&act, sizeof(act));
	act.sa_handler = sig_handler;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	if (ac < 2 || strcmp(av[1], "-h") == 0 || strcmp(av[1], "--help") == 0)
		return (help(0));
	else if (ac < 2 || ac != 2 || port <= 0)
		return (help(84));
	manager.serv_fd = init_socket(port, &manager);
	manager.fd_max = manager.serv_fd;
	if (manager.serv_fd < 0)
		return (84);
	main_loop(&manager);
	return (0);
}