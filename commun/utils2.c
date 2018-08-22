/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commun.h"

static int count_sep(const char *str, char sep)
{
	int nb_sep = 0;

	if (str == NULL)
		return (0);
	for (int i = 0; str[i] != '\0'; ++i) {
	if (str[i] == sep)
		nb_sep += 1;
	}
	return (nb_sep);
}

static char **file(char **res, const char *str, char sep)
{
	int x = 0;

	res[x] = NULL;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == sep) {
			++x;
			res[x] = NULL;
		} else
			res[x] = my_charcat(res[x], str[i]);
	}
	++x;
	res[x] = NULL;
	return (res);
}

char **str_to_arr(const char *str, char sep, const char *epur)
{
  char *tmp = NULL;
	int nb_sep = 0;
	char **res;

	if (str == NULL)
		return (NULL);
	tmp = strdup(str);
	tmp = epur_str(tmp, epur);
	if (tmp == NULL)
		return (NULL);
	nb_sep = count_sep(tmp, sep);
	if (tmp == NULL)
		return (NULL);
	res = malloc(sizeof(char *) * (nb_sep + 2));
	if (res == NULL)
		return (NULL);
	file(res, tmp, sep);
	free(tmp);
	return (res);
}
