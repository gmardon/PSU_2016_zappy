/*
** map.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/IA/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Wed Jun 15 09:48:45 2016 quentin quero
** Last update Fri Jun 24 17:09:09 2016 quentin quero
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
