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

client_list_t *find_client(client_list_t *client, const char *nick_name)
{
	for (; client; client = client->next) {
		if (client->nick_name &&
			strcmp(client->nick_name, nick_name) == 0)
			break;
	}
	return (client);
}

char is_alpha_num(const char *str)
{
	if (str == NULL)
		return (FALSE);
	for (int i = 0; str[i] != '\0'; ++i) {
		if (isalnum((int)str[i]) == 0
			&& str[i] != '_' && str[i] != '-')
			return (FALSE);
	}
	return (TRUE);
}

static char verif_nick(control_struct_t *manager, data_struct_t *data)
{
	if (data->args[1] == NULL) {
		print_format(data, manager->ip, NO_NICK_SET);
		return (1);
	} else if (find_client(manager->head_client, data->args[1])) {
		print_format(data, manager->ip, NICK_USED);
		return (1);
	} else if (is_alpha_num(data->args[1]) != TRUE) {
		print_format(data, manager->ip, BAD_NICK);
		return (1);
	}
	return (0);
}

void init_nickname(control_struct_t *manager, data_struct_t *data)
{
	if (verif_nick(manager, data) == 1)
		return;
	else if ((*data->client)->nick_name != NULL)
		print_format(data, manager->ip, data->args[1]);
	send_to_all_chans((*data->client)->wrap_chan_h, data,
	data->args[1], manager->ip);
	free((*data->client)->nick_name);
	(*data->client)->nick_name = strdup(data->args[1]);
}