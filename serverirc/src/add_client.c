/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

client_list_t *add_client(control_struct_t *manager, int fd)
{
	client_list_t *tmp = manager->head_client;
	client_list_t *add = new_client(fd);

	if (!add) {
		return (manager->head_client);
	} else if (tmp == NULL || add->fd > tmp->fd) {
		manager->fd_max = add->fd;
		add->next = tmp;
		return (add);
	}
	for (; tmp && tmp->next && tmp->next->fd > fd; tmp = tmp->next);
	if (tmp) {
		add->next = tmp->next;
		tmp->next = add;
	}
	return (manager->head_client);
}