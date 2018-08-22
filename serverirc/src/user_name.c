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

static int size_args(char **arr)
{
	int i = 0;

	if (arr == NULL || arr[0] == NULL)
		return (0);
	for (; arr[i]; ++i);
	return (i);
}

void user_name(control_struct_t *manager, data_struct_t *data)
{
	if ((*data->client)->user_name != NULL ||
		size_args(&data->args[1]) != 4)
		return;
	(void)manager;
	free((*data->client)->user_name);
	(*data->client)->user_name = strdup(data->args[4]);
	dprintf((*data->client)->fd, "%s\r\n", CONNECT_OK);
}