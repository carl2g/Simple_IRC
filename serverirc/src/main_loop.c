/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <strings.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include "server.h"

static int accept_connection(int serv_fd)
{
	int c_fd = accept(serv_fd, NULL, NULL);

	if (c_fd < 0) {
		perror("accept()");
		return (-1);
	}
	return (c_fd);
}

static void init_for_select(control_struct_t *manager, struct timeval *tmo)
{
	client_list_t *tmp = manager->head_client;

	FD_ZERO(&manager->writefds);
	FD_ZERO(&manager->readfds);
	tmo->tv_sec = 0;
	tmo->tv_usec = 50000;
	FD_SET(manager->serv_fd, &manager->readfds);
	for (; tmp; tmp = tmp->next) {
		FD_SET(tmp->fd, &manager->readfds);
	}
}

static void accept_client(control_struct_t *manager)
{
	int new_client_fd;
	client_list_t *new_client = NULL;

	if (FD_ISSET(manager->serv_fd, &manager->readfds) > 0) {
		new_client_fd = accept_connection(manager->serv_fd);
		if (new_client_fd > 0) {
			new_client = add_client(manager, new_client_fd);
			manager->head_client = new_client;
		}
	}
}

void main_loop(control_struct_t *manager)
{
	struct	timeval tmo;

	while (exit_sig != 1) {
		init_for_select(manager, &tmo);
		select(manager->fd_max + 1, &manager->readfds,
		&manager->writefds, NULL, &tmo);
		read_form_client(manager);
		accept_client(manager);
	}
	clean_client_list(manager->head_client);
	remove_all_chan(manager->head_chan);
	free(manager->ip);
	close(manager->serv_fd);
}