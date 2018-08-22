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

void client_quit(control_struct_t *manager, data_struct_t *data)
{
	const char *msg = get_string_at(data->cmd, ":");

	if (msg) {
		send_to_all_chans((*data->client)->wrap_chan_h, data,
		msg, manager->ip);
	} else
		send_to_all_chans((*data->client)->wrap_chan_h, data,
		DEFAULT_QUIT_MSG, manager->ip);
	remove_client_from_list(manager, data->client);
}