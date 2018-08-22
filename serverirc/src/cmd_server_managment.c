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

chan_wrapper_t *find_chan_w(chan_wrapper_t *chan, const char *chan_name)
{
	for (; chan; chan = chan->next) {
		if (strcmp(chan->chan->chan_name, chan_name) == 0)
			break;
	}
	return (chan);
}

void switch_chan(control_struct_t *manager, data_struct_t *data)
{
	chan_wrapper_t *w_chan = NULL;

	(void)manager;
	if (data->args[1] == NULL)
		return;
	w_chan = find_chan_w((*data->client)->wrap_chan_h, data->args[1]);
	if (!w_chan)
		return;
	w_chan = pop_chan_wrap(w_chan, &((*data->client)->wrap_chan_h));
	w_chan->next = (*data->client)->wrap_chan_h;
	(*data->client)->wrap_chan_h->prev = w_chan;
	(*data->client)->wrap_chan_h = w_chan;
}

void send_to_all_chans(chan_wrapper_t *w_chan, data_struct_t *data,
	const char *msg, const char *ip)
{
	for (; w_chan; w_chan = w_chan->next) {
		triger_send_to_chan(w_chan, data, msg, ip);
	}
}

char triger_send_to_chan(chan_wrapper_t *w_chan, data_struct_t *data,
	const char *msg, const char *ip)
{
	client_wrapper_t *w_client = NULL;

	if (!w_chan)
		return (-1);
	w_client = w_chan->chan->h_client_wrap;
	for (; w_client; w_client = w_client->next) {
		if (*data->client != w_client->client) {
			dprintf(w_client->client->fd, "%s %s@%s %s :%s\r\n",
			data->args[0], (*data->client)->nick_name, ip,
			w_chan->chan->chan_name, msg);
		}
	}
	return (0);
}

void send_mesg(control_struct_t *manager, data_struct_t *data)
{
	(void)manager;
	(void)data;
}