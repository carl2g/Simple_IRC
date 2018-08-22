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

void list_all_users(control_struct_t *manager, data_struct_t *data)
{
	client_list_t *tmp = manager->head_client;

	dprintf((*data->client)->fd, "%s\r\n", INFO_USERS);
	for (; tmp; tmp = tmp->next) {
		dprintf((*data->client)->fd, "%s\r\n", tmp->nick_name);
	}
}

void list_all_chan(control_struct_t *manager, data_struct_t *data)
{
	chanel_list_t *tmp = manager->head_chan;

	if (data->args[1] != NULL) {
		list_chan_with_string(manager, data);
		return;
	}
	dprintf((*data->client)->fd, "%s\r\n", RPL_L_START);
	for (; tmp; tmp = tmp->next) {
		dprintf((*data->client)->fd, "%s %s\r\n",
		LIST_OK, tmp->chan_name);
	}
	dprintf((*data->client)->fd, "%s\r\n", RPL_L_END);
}

static void contain_str(data_struct_t *data, const char *actual_name)
{
	for (int i = 0; data->cmd_args[i] != NULL; ++i) {
		if (strstr(actual_name, data->cmd_args[i]) != NULL) {
			dprintf((*data->client)->fd, "%s %s\r\n",
			LIST_OK, actual_name);
			break;
		}
	}
}

void list_chan_with_string(control_struct_t *manager, data_struct_t *data)
{
	chanel_list_t *tmp = NULL;

	if (data->cmd_args == NULL)
		return;
	tmp = manager->head_chan;
	dprintf((*data->client)->fd, "%s\r\n", RPL_L_START);
	for (; tmp; tmp = tmp->next) {
		contain_str(data, tmp->chan_name);
	}
	dprintf((*data->client)->fd, "%s\r\n", RPL_L_END);
}