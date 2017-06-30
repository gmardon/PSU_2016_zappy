/*
** take.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:28:03 2017 Julien Nabti
** Last update Fri Jun 30 17:28:04 2017 Julien Nabti
*/


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ai.h"

//////////////// TODO Norme / fonction ///////////////////////

struct s_rscs rscs_tab[7] = {
  {"nourriture", &take_food},
  {"linemate", &take_linemate},
  {"deraumere", &take_deraumere},
  {"sibur", &take_sibur},
  {"mendiane", &take_mendiane},
  {"phiras", &take_phiras},
  {"thystame", &take_thystame},
};

int
get_rscs_index(char *cmd)
{
  int i;

  i = 0;
  while (i < 6)
  {
    if (strcmp(rscs_tab[i].key, cmd) == 0)
      return (i);
    ++i;
  }
  return (-1);
}

void
send_take(struct s_client *client, char *cmd)
{
  int i;

  i = get_rscs_index(cmd);
  if (i == -1)
    return;
  rscs_tab[i].fptr(client);
}
