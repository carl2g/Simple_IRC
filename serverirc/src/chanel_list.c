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

static chanel_list_t *new_chan(const char *chan_name)
{
	chanel_list_t *new_chan = malloc(sizeof(chanel_list_t));

	if (new_chan == NULL)
		return (NULL);
	new_chan->next = NULL;
	new_chan->h_client_wrap = NULL;
	new_chan->chan_name = strdup(chan_name);
	return (new_chan);
}

static chanel_list_t *add_chan(control_struct_t *manager,
	const char *chan_name)
{
	chanel_list_t *add_chan = new_chan(chan_name);

	if (add_chan == NULL)
		return (manager->head_chan);
	add_chan->next = manager->head_chan;
	manager->head_chan = add_chan;
	return (add_chan);
}

void remove_all_chan(chanel_list_t *chan)
{
	if (chan) {
		free((char *)chan->chan_name);
		clean_client_wrap_list(chan->h_client_wrap);
		remove_all_chan(chan->next);
		free(chan);
	}
}

void add_client_to_chan(control_struct_t *manager,
	const char *chan_name, client_list_t *client)
{
	chanel_list_t *tmp = manager->head_chan;

	for (; tmp; tmp = tmp->next) {
		if (strcmp(tmp->chan_name, chan_name) == 0)
			break;
	}
	if (!tmp) {
		tmp = add_chan(manager, chan_name);
	}
	add_wrap_client(tmp, client);
	add_wrap_chan(client, tmp);
}