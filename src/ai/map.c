/*
** map.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:29:45 2017 Julien Nabti
** Last update Fri Jun 30 17:29:45 2017 Julien Nabti
*/


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "ai.h"

void aff_map(struct s_map * map)
{
  int i;

  i = 0;
  while (i < X_MAX * Y_MAX)
  {
    if (map[i].nbr_player > 0) {
      printf("%d", map[i].nbr_player);
    }
    else
    printf(".");
    if ((i + 1) % X_MAX == 0) {
      printf("\n");
    }
    i++;
  }
}

void sync_map(struct s_map * map, struct s_players * players)
{
  int i;

  i = 0;
  while (i < X_MAX * Y_MAX)
  {
      if (((X_MAX * players->Y) + players->X) == i)
      {
        map[i].nbr_player += 1;
      }
    i++;
  }
}

void clear_map(struct s_map * map)
{
  int i;

  i = 0;
  while (i < X_MAX * Y_MAX)
  {
    map[i].nbr_player = 0;
    i++;
  }
}
