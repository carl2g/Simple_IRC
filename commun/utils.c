/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commun.h"

int my_strlen(const char *s)
{
	int x = 0;

	if (s == NULL)
		return (0);
	for (; s[x] != '\0'; ++x);
	return (x);
}

char *my_strcat(char *s1, const char *s2)
{
	int x = my_strlen(s1);
	s1 = realloc(s1, sizeof(char) * (my_strlen(s1) +
	+ my_strlen(s2)) + sizeof(char));

	if (s2 != NULL)
		for (int i = 0; s2[i] != '\0'; ++i) {
			s1[x] = s2[i];
			x = x + 1;
		}
	s1[x] = '\0';
	return (s1);
}

char *my_charcat(char *s1, char c)
{
	int len = my_strlen(s1);

	s1 = realloc(s1, sizeof(char) * (len + 2));
	s1[len] = c;
	++len;
	s1[len] = '\0';
	return (s1);
}

static void utils_epur(const char *epur, char *str, int *i)
{
	char increm = 0;

	for (int x = 0; epur[x] != '\0'; ++x) {
		for (; str[*i] == epur[x]; ++*i) {
			x = 0;
			increm = 1;
		}
	}
	if (increm == 0)
		++*i;
}

char *epur_str(char *str, const char *epur)
{
	char *res = NULL;
	int i = 0;

	if (str == NULL)
		return (NULL);
	for (int x = 0; epur[x] != '\0'; ++x){
		for (; str[i] == epur[x]; ++i)
			x = 0;
	}
	while (str[i] != '\0') {
		res = my_charcat(res, str[i]);
		utils_epur(epur, str, &i);
	}
	free(str);
	return (res);
}