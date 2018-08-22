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

static char check_log(data_struct_t *data)
{
	if ((*data->client)->nick_name != NULL &&
		strcmp(data->args[0], USER) == 0)
		return (0);
	else if (strcmp(data->args[0], NICK) == 0)
		return (0);
	if ((*data->client)->user_name != NULL
		&& (*data->client)->nick_name != NULL)
		return (0);
	else if (strcmp(data->args[0], QUIT) == 0)
		return (0);
	free(data->cmd);
	free_arr(data->cmd_args);
	free_arr(data->args);
	return (1);
}

static void exe_cmd(control_struct_t *manager, data_struct_t *data, int len)
{
	int x = 0;

	if (len >= 1 && data->cmd[len - 1] == '\r')
		data->cmd[len - 1] = '\0';
	data->args = str_to_arr(data->cmd, ' ', "\t ");
	if (data->args == NULL || data->args[0] == NULL)
		return;
	data->cmd_args = str_to_arr(data->args[1], ',', ",");
	if (check_log(data) == 1)
		return;
	for (; func_tab[x].cmd != NULL &&
		strcmp(func_tab[x].cmd, data->args[0]) != 0; ++x);
	func_tab[x].func(manager, data);
	free(data->cmd);
	free_arr(data->cmd_args);
	free_arr(data->args);
}

static void launch_cmd(control_struct_t *manager,
	client_list_t **client, int end)
{
	int len = 0;
	data_struct_t data = {.client = client, .cmd = NULL};

	for (int i = manager->circ_buff.head; i != end; ) {
		if (manager->circ_buff.buff[i] != '\n')
			data.cmd = my_charcat(data.cmd,
			manager->circ_buff.buff[i]);
		i = (i + 1) % READ_SIZE;
		if (manager->circ_buff.buff[i] == '\n') {
			len = my_strlen(data.cmd);
			printf("CMD = %d %s\n", (*client)->fd, data.cmd);
			exe_cmd(manager, &data, len);
			data.cmd = NULL;
		}
	}
}

static void read_or_disconnect(control_struct_t *manager,
	client_list_t **client)
{
	int len = 0;
	int tail = manager->circ_buff.head;
	int *head = &manager->circ_buff.head;

	while ((len = read((*client)->fd,
		&manager->circ_buff.buff[tail], (READ_SIZE - tail))) > 0) {
		tail += len;
		if (manager->circ_buff.buff[tail - 1] == '\n') {
			break;
		}
		tail = tail % READ_SIZE;
	}
	if (len == 0) {
		client_quit(manager, &(data_struct_t){.client = client,
		.args = (char *[]){QUIT, NULL}, .cmd_args = NULL });
		return;
	}
	launch_cmd(manager, client, tail - 1);
	*head = tail % READ_SIZE;
}

void read_form_client(control_struct_t *manager)
{
	client_list_t *tmp = manager->head_client;

	while (tmp) {
		if (FD_ISSET(tmp->fd, &manager->readfds) > 0) {
			read_or_disconnect(manager, &tmp);
		}
		if (tmp)
			tmp = tmp->next;
	}
}