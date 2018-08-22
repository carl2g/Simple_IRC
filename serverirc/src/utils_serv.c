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

chanel_list_t *find_chan(const char *chan_name, control_struct_t *manager)
{
	chanel_list_t *tmp = manager->head_chan;

	for (; tmp; tmp = tmp->next) {
		if (strcmp(chan_name, tmp->chan_name) == 0){
			break;
		}
	}
	return (tmp);
}

void print_format(data_struct_t *data, const char *ip,
	const char *msg)
{
	dprintf((*data->client)->fd, ":%s!%s@%s %s :%s\r\n",
	(*data->client)->nick_name, (*data->client)->user_name,
	ip, data->args[0], msg);
}

void print_format_prv_msg(data_struct_t *data, const char *ip,
	const char *msg, const char *reciver)
{
	dprintf((*data->client)->fd, ":%s!%s@%s %s %s :%s\r\n",
	(*data->client)->nick_name, (*data->client)->user_name,
	ip, data->args[0], reciver, msg);
}