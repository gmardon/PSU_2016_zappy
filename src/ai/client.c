/*
** client.c for zappy_ai in /home/danibo_a/Documents/Epitech/tek2/PSU_2015_zappy/client
**
** Made by Daniboon
** Login   <danibo_a@epitech.net>
**
** Started on  Thu Jun 16 00:52:03 2016 Daniboon
** Last update Sun Jun 26 19:12:03 2016 quentin quero
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include "ai.h"

/*
**  Création/connection du client
**  Lancement de la boucle autonome
*/

static int socket_create(struct s_client *client)
{
    int rc;

    client->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client->fd == -1)
        return (-1);
    client->server_addr.sin_family = AF_INET;
    client->server_addr.sin_port = htons(client->options->port);
    rc = inet_pton(AF_INET, client->options->hostname,
                   &client->server_addr.sin_addr);
    if (rc == 0)
        return (-1);
    rc = connect(client->fd, (struct sockaddr *) &client->server_addr,
                 sizeof(client->server_addr));
    if (rc == -1)
        return (-1);
    return (0);
}

int launch_client(struct s_client * client)
{
    char    buff[100];
    int     rc;

    rc = socket_create(client);
    if (rc == -1)
        return (-1);
    rc = read(client->fd, buff, 99);
    if (rc == -1)
        return (-1);
    write(1, buff, rc);
    write(client->fd, client->options->team, strlen(client->options->team));
    write(client->fd, "\n", 1);
    rc = read(client->fd, buff, 99);
    buff[rc] = '\0';
    X_MAX = atoi(buff);
    Y_MAX = atoi (&buff[2]);
    client->end = 0;
    ia(client);
    return (0);
}
