/*
** send.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Sat Jun 18 11:25:34 2016 quentin quero
** Last update Tue Jun 21 14:43:28 2016 quentin quero
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ai.h"

void
send_go(struct s_client *client)
{
  send(client->fd, "avance\n", 7, 0);
}

void
send_right(struct s_client *client)
{
  send(client->fd, "droite\n", 7, 0);
}

void
send_left(struct s_client *client)
{
  send(client->fd, "gauche\n", 7, 0);
}

void
send_see(struct s_client *client)
{
  send(client->fd, "voir\n", 5, 0);
}

void
send_stuff(struct s_client *client)
{
  send(client-> fd, "inventaire\n", 11, 0);
}

void
send_lay(struct s_client *client, char *obj)
{
  char *str;
  int  buff_size;

  buff_size = sizeof("pose ") + sizeof(obj);
  str = malloc(buff_size + 1);
  str[buff_size] = '\0';
  snprintf(str, buff_size, "pose %s\n", obj);
  send(client->fd, str, (int)strlen(str), 0);
}

void
send_expulse(struct s_client *client)
{
  send(client->fd, "expulse\n", 8, 0);
}

void
send_broadcast(struct s_client *client, char * txt)
{
  char *str;
  int  buff_size;

  buff_size = sizeof("broadcast ") + sizeof(txt);
  str = malloc(buff_size + 1);
  str[buff_size] = '\0';
  snprintf(str, buff_size , "broadcast %s\n", txt);
  send(client->fd, str, (int)strlen(str), 0);
}

void
send_incantation(struct s_client *client)
{
  send(client->fd, "incantation\n", 12, 0);
}

void
send_fork(struct s_client *client)
{
  send(client->fd, "fork\n", 5, 0);
}

void
send_connect(struct s_client *client)
{
  send(client->fd, "connect_nbr\n", 12, 0);
}

void
send_dead(struct s_client *client)
{
  send(client->fd, "-\n", 2, 0);
}
