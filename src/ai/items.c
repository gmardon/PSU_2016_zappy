/*
** items.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:27:06 2017 Julien Nabti
** Last update Fri Jun 30 17:28:56 2017 Julien Nabti
*/


#include <stdlib.h>
#include <unistd.h>
#include "ai.h"

void take_food(struct s_client * client)
{
  send(client->fd, "prend nourriture\n", 17, 0);
}

void take_linemate(struct s_client * client)
{
  send(client->fd, "prend linemate\n", 15, 0);
}

void take_deraumere(struct s_client * client)
{
  send(client->fd, "prend deraumere\n", 14, 0);
}

void take_sibur(struct s_client * client)
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
