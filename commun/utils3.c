/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "commun.h"
#include "server.h"

void free_arr(char **arr)
{
	if (arr == NULL || arr[0] == NULL)
		return;
	for (int i = 0; arr[i] != NULL; ++i) {
		free(arr[i]);
	}
	free(arr);
}

const char *get_string_at(const char *str, const char *to_find)
{
	char *found = NULL;

	if (str == NULL)
		return (NULL);
	found = strstr(str, to_find);
	if (found != NULL)
		found += my_strlen(to_find) * sizeof(char);
	return(found);
}