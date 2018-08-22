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

chan_wrapper_t *pop_chan_wrap(chan_wrapper_t *w, chan_wrapper_t **head)
{
	chan_wrapper_t *tmp = w;

	if (*head == w)
		*head = (*head)->next;
	if (w->next) {
		tmp = tmp->next;
		tmp->prev = w->prev;
	}
	if (w->prev) {
		tmp = w;
		tmp->prev->next = w->next;
	}
	return (w);
}

void rm_chan_wrap(chan_wrapper_t *w, chan_wrapper_t **head)
{
	free(pop_chan_wrap(w, head));
}

void add_wrap_chan(client_list_t *client, chanel_list_t *add_chan)
{
	chan_wrapper_t *chan_wrap = malloc(sizeof(chan_wrapper_t));

	if (chan_wrap == NULL)
		return;
	chan_wrap->chan = add_chan;
	chan_wrap->next = client->wrap_chan_h;
	if (client->wrap_chan_h)
		client->wrap_chan_h->prev = chan_wrap;
	chan_wrap->prev = NULL;
	client->wrap_chan_h = chan_wrap;
}

static void clean_chan_wrap(client_wrapper_t *tmp_client_w,
	chan_wrapper_t *tmp_chan, client_list_t *client)
{
	while (tmp_client_w) {
		if (tmp_client_w->client == client) {
			tmp_client_w = rm_client_wrap(tmp_client_w,
			&tmp_chan->chan->h_client_wrap);
			break;
		}
		else
			tmp_client_w = tmp_client_w->next;
	}
}

void clean_chan_wrap_list(chan_wrapper_t *chan_wrap, client_list_t *client)
{
	client_wrapper_t *tmp_client_w = NULL;

	if (chan_wrap) {
		tmp_client_w = chan_wrap->chan->h_client_wrap;
		clean_chan_wrap(tmp_client_w, chan_wrap, client);
		clean_chan_wrap_list(chan_wrap->next, client);
		free(chan_wrap);
	}
}