/*
** EPITECH PROJECT, 2018
** project
** File description:
** file description
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "server.h"

static int create_socket(void)
{
	int fd = socket(PF_INET, SOCK_STREAM, 0);

	if (fd < 0) {
		perror("socket()");
		return (-1);
	}
	return (fd);
}

static int bind_and_listen(int serv_fd, struct sockaddr_in *sock)
{
	if (bind(serv_fd,
		(struct sockaddr *)sock, sizeof(*sock)) == -1) {
		perror("bind()");
		return (-1);
	}
	if (listen(serv_fd, 0) == -1) {
		perror("listen()");
		return (-1);
	}
	return (0);
}

static void init_socket_struct(struct sockaddr_in *sock,
	int family, int port, int ip)
{
	bzero(sock, sizeof(*sock));
	sock->sin_family = family;
	sock->sin_port = htons(port);
	sock->sin_addr.s_addr = ip;
}

static char *get_ip_add(void)
{
	struct ifaddrs *ifap = NULL;
	struct ifaddrs *tmp = NULL;
	struct sockaddr_in *pAddr = NULL;
	char *res = NULL;

	getifaddrs(&ifap);
	tmp = ifap;
	while (tmp) {
		if (tmp->ifa_name &&
			strcmp(tmp->ifa_name, "wlp2s0") == 0 &&
			tmp->ifa_addr && tmp->ifa_addr->sa_family == PF_INET) {
			pAddr = (struct sockaddr_in *)tmp->ifa_addr;
			res = strdup(inet_ntoa(pAddr->sin_addr));
			break;
		}
		tmp = tmp->ifa_next;
	}
	freeifaddrs(ifap);
	return (res);
}

int init_socket(int port, control_struct_t *m)
{
	int serv_fd = create_socket();
	struct sockaddr_in sock;

	if (serv_fd == -1)
		return (-1);
	init_socket_struct(&sock, PF_INET, port, INADDR_ANY);
	if (bind_and_listen(serv_fd, &sock) < 0)
		return (-1);
	m->ip = get_ip_add();
	if (m->ip == NULL)
		m->ip = strdup("127.0.0.1");
	return (serv_fd);
}