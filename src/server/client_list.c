/*
** client_list.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
** 
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
** 
** Started on  Mon Jun 26 16:58:18 2017 Aurelien
** Last update Mon Jun 26 16:58:30 2017 Aurelien
*/
#include "server.h"

int add_client(t_server *server, t_client *client)
{
    t_clist *tmp;
    t_clist *new;

    tmp = server->client_list;
    while (tmp != NULL && tmp->next != NULL)
        tmp = tmp->next;
    if ((new = malloc(sizeof(t_clist))) == NULL)
        return (1);
    new->client = client;
    if (tmp == NULL)
        server->client_list = new;
    else
        tmp->next = new;
    return (0);
}

int del_client(t_server *server, int fd)
{
    t_clist *tmp;
    t_clist *old;

    tmp = server->client_list;
    old = NULL;
    while (tmp != NULL)
    {
        if (tmp->client->fd == fd)
            break;
        old = tmp;
        tmp = tmp->next;
    }
    if (tmp == NULL)
        return (1);
    if (old == NULL)
        server->client_list = tmp->next;
    else
        old->next = tmp->next;
    free(tmp->client);
    free(tmp);
    return (0);
}

int clients_length(t_clist *client_list)
{
    t_clist *tmp;
    int i;

    i = 0;
    tmp = client_list;
    while (tmp != NULL)
    {
        tmp = tmp->next;
        i++;
    }
    return (i);
}