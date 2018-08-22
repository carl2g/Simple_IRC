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

static char all_rady_in_chan(control_struct_t *manager,
	data_struct_t *data, const char *chan_name)
{
	chanel_list_t *chan = find_chan(chan_name, manager);

	if (chan && find_client_in_chan(chan, *data->client)) {
		return (1);
	}
	return (0);
}

static char is_chan(const char *str)
{
	if (str == NULL)
		return (0);
	return (str[0] == '#' || str[0] == '&');
}

void join_chan(control_struct_t *manager, data_struct_t *data)
{
	chanel_list_t *tmp = NULL;

	if (data->cmd_args == NULL || data->cmd_args[0] == NULL)
		return;
	for (int i = 0; data->cmd_args[i] != NULL; ++i) {
		if (all_rady_in_chan(manager, data, data->cmd_args[i]) == 0
			&& is_chan(data->cmd_args[i])) {
			add_client_to_chan(manager,
			data->cmd_args[i], (*data->client));
			print_format(data, manager->ip,
			data->cmd_args[i]);
			tmp = find_chan(data->cmd_args[i], manager);
			print_all_user_in_chan(*data->client, tmp);
			send_to_chan(data, "Welcome him!!!",
			data->cmd_args[i], manager->ip);
		} else {
			dprintf((*data->client)->fd, "%s\r\n", NO_SUCH_CHAN);
		}
	}
}