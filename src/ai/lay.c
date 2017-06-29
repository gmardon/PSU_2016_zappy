/*
** lay.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Thu Jun 16 15:05:41 2016 quentin quero
** Last update Fri Jun 17 10:42:18 2016 quentin quero
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ai.h"

//////////////// TODO Norme / fonction ///////////////////////

int lay_linemate(struct s_map * map, struct s_players * player) {
  map[(X_MAX * player->Y) + player->X].linemate = player->linemate;
  player->linemate = 0;
  return 0;
}

int lay_deraumere(struct s_map * map, struct s_players * player) {
  map[(X_MAX * player->Y) + player->X].deraumere = player->deraumere;
  player->deraumere = 0;
  return 0;
}

int lay_sibur(struct s_map * map, struct s_players * player) {
  map[(X_MAX * player->Y) + player->X].sibur = player->sibur;
  player->sibur = 0;
  return 0;
}

int lay_mendiane(struct s_map * map, struct s_players * player) {
  map[(X_MAX * player->Y) + player->X].mendiane = player->mendiane;
  player->mendiane = 0;
  return 0;
}

int lay_phiras(struct s_map * map, struct s_players * player) {
  map[(X_MAX * player->Y) + player->X].phiras = player->phiras;
  player->phiras = 0;
  return 0;
}

int lay_thystame(struct s_map * map, struct s_players * player) {
  map[(X_MAX * player->Y) + player->X].thystame = player->thystame;
  player->thystame = 0;
  return 0;
}

int lay(struct s_map * map, struct s_players * player, char *cmd) {
  if(strcmp(cmd, "linemate")) {
    lay_linemate(map, player);
  }
  else if(strcmp(cmd, "deraumere")) {
    lay_deraumere(map, player);
  }
  else if(strcmp(cmd, "sibur")) {
    lay_sibur(map, player);
  }
  else if(strcmp(cmd, "mendiane")) {
    lay_mendiane(map, player);
  }
  else if(strcmp(cmd, "phiras")) {
    lay_phiras(map, player);
  }
  else if(strcmp(cmd, "thystame")) {
    lay_thystame(map, player);
  }
  else {
    return -1;
  }
  return 0;
}
