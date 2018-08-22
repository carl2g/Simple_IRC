/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "server.h"

void print_prv_msg(data_struct_t *data, client_list_t *client,
	const char *msg, const char *ip)
{
	if (!client) {
		dprintf((*data->client)->fd, "%s\r\n", NO_SUCH_NICK);
		return;
	}
	dprintf(client->fd, "%s %s@%s :%s\r\n",
	data->args[0], (*data->client)->nick_name, ip, msg);
}

char send_to_chan(data_struct_t *data, const char *msg,
	const char *chan_name, const char *ip)
{
	chan_wrapper_t *w_chan =
	find_chan_w((*data->client)->wrap_chan_h, chan_name);
	triger_send_to_chan(w_chan, data, msg, ip);
	return (0);
}

static void send_client(control_struct_t *manager, data_struct_t *data,
	const char *c_nick, const char *msg)
{
	client_list_t *client = find_client(manager->head_client, c_nick);

	if (client == NULL)
		return;
	print_format_prv_msg(data, manager->ip, msg, client->nick_name);
	print_prv_msg(data, client, msg, manager->ip);
}

void priv_mesg(control_struct_t *manager, data_struct_t *data)
{
	const char *msg = get_string_at(data->cmd, ":");

	if (msg == NULL) {
		print_format(data, manager->ip, NO_TEXT_TO_SEND);
		return;
	}
	for (int i = 0; data->cmd_args[i] != NULL; ++i) {
		if (data->cmd_args[i][0] == '#' ||
			data->cmd_args[i][0] == '&') {
			print_format_prv_msg(data, manager->ip, msg,
			data->cmd_args[i]);
			send_to_chan(data, msg,
			data->cmd_args[i], manager->ip);
		} else {
			send_client(manager, data, data->cmd_args[i], msg);
		}
	}
}