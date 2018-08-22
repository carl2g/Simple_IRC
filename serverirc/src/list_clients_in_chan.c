/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void print_all_user_in_chan(client_list_t *c, chanel_list_t *h)
{
	client_wrapper_t *w = NULL;

	if (h == NULL || c == NULL)
		return;
	w = h->h_client_wrap;
	for (; w; w = w->next) {
		dprintf(c->fd, "%s %s\r\n",
		NAMES_LIST, w->client->nick_name);
	}
}

void list_client_in_chan(control_struct_t *manager, data_struct_t *data)
{
	chanel_list_t *tmp = NULL;

	if (data->args[1] == NULL)
		return;
	for (int i = 0; data->cmd_args[i] != NULL; ++i) {
		tmp = find_chan(data->cmd_args[i], manager);
		if (tmp != NULL) {
			dprintf((*data->client)->fd, "%s\r\n", RPL_L_START);
			print_all_user_in_chan(*data->client, tmp);
			dprintf((*data->client)->fd, "%s\r\n", RPL_L_END);
		}
	}
}