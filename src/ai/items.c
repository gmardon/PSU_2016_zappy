/*
** items.c for zappy_ai in /home/danibo_a/Documents/Epitech/tek2/PSU_2015_zappy/client/src
**
** Made by Daniboon
** Login   <danibo_a@epitech.net>
**
** Started on  Mon Jun 20 17:51:03 2016 Daniboon
** Last update Mon Jun 27 10:48:25 2016 quentin quero
*/

#include <stdlib.h>
#include <unistd.h>
#include "ai.h"

void
take_food(struct s_client * client)
{
  send(client->fd, "prend nourriture\n", 17, 0);
}

void
take_linemate(struct s_client * client)
{
  send(client->fd, "prend linemate\n", 15, 0);
}

void
take_deraumere(struct s_client * client)
{
  send(client->fd, "prend deraumere\n", 14, 0);
}

void
take_sibur(struct s_client * client)
{
  send(client->fd, "prend sibur\n", 12, 0);
}

void
take_mendiane(struct s_client * client)
{
  send(client->fd, "prend mendiane\n", 15, 0);
}

void
take_phiras(struct s_client * client)
{
  send(client->fd, "prend phiras\n", 13, 0);
}

void
take_thystame(struct s_client * client)
{
  send(client->fd, "prend thystame\n", 15, 0);
}
