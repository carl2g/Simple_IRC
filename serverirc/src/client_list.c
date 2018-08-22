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

client_list_t *new_client(int fd)
{
	client_list_t *new = malloc(sizeof(client_list_t));

	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->wrap_chan_h = NULL;
	new->nick_name = NULL;
	new->user_name = NULL;
	new->fd = fd;
	return (new);
}

static void remove_client(client_list_t *client)
{
	free(client->nick_name);
	free(client->user_name);
	clean_chan_wrap_list(client->wrap_chan_h, client);
	close(client->fd);
	free(client);
}

void clean_client_list(client_list_t *head)
{
	if (head) {
		clean_client_list(head->next);
		remove_client(head);
	}
}

void remove_client_from_list(control_struct_t *manager,
	client_list_t **to_remove)
{
	client_list_t *tmp = manager->head_client;

	if (manager->head_client && *to_remove == manager->head_client) {
		tmp = (*to_remove)->next;
		remove_client(*to_remove);
		*to_remove = tmp;
		manager->head_client = tmp;
		if (tmp)
			manager->fd_max = manager->head_client->fd;
		return;
	}
	for (; tmp && tmp->next && tmp->next != *to_remove; tmp = tmp->next);
	if (tmp) {
		tmp->next = (*to_remove)->next;
		remove_client(*to_remove);
		*to_remove = tmp->next;
	}
}