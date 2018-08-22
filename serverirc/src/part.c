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

void leave_chan(control_struct_t *manager, data_struct_t *data)
{
	if (data->cmd_args == NULL)
		return;
	for (int i = 0; data->cmd_args[i] != NULL; ++i) {
		print_format(data, manager->ip, data->cmd_args[i]);
		send_to_chan(data, DEFAULT_QUIT_MSG,
		data->cmd_args[i], manager->ip);
		pop_client_wrap(manager, data->cmd_args[i], (*data->client));
	}
}