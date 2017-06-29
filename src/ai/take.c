/*
** take.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Thu Jun 16 14:40:40 2016 quentin quero
** Last update Sun Jun 26 22:00:10 2016 quentin quero
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
