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

client_wrapper_t *find_client_in_chan(chanel_list_t *chan,
	client_list_t *client)
{
	client_wrapper_t *tmp = chan->h_client_wrap;

	for (; tmp; tmp = tmp->next) {
		if (tmp->client == client) {
			break;
		}
	}
	return (tmp);
}

void clean_client_wrap_list(client_wrapper_t *wrap)
{
	if (wrap) {
		clean_client_wrap_list(wrap->next);
		free(wrap);
	}
}

void pop_client_wrap(control_struct_t *manager,
	const char *chan_name, client_list_t *client)
{
	chanel_list_t *chan = find_chan(chan_name, manager);
	client_wrapper_t *w = NULL;

	if (!chan)
		return;
	w = find_client_in_chan(chan, client);
	if (!w)
		return;
	rm_client_wrap(w, &chan->h_client_wrap);
}

client_wrapper_t *rm_client_wrap(client_wrapper_t *w, client_wrapper_t **head)
{
	client_wrapper_t *tmp = NULL;

	if (*head == w)
		*head = (*head)->next;
	if (w->prev) {
		tmp = w->prev;
		tmp->next = (w)->next;
	}
	if (w->next) {
		tmp = w->next;
		tmp->prev = w->prev;
	}
	free(w);
	return (tmp);
}

void add_wrap_client(chanel_list_t *chan, client_list_t *client)
{
	client_wrapper_t *wrap = malloc(sizeof(client_wrapper_t));

	if (wrap == NULL || chan == NULL)
		return;
	wrap->client = client;
	wrap->next = chan->h_client_wrap;
	if (chan->h_client_wrap)
		chan->h_client_wrap->prev = wrap;
	wrap->prev = NULL;
	chan->h_client_wrap = wrap;
}