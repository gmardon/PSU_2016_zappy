/*
** init.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Mon Jun 27 11:08:55 2016 quentin quero
** Last update Mon Jun 27 11:13:11 2016 quentin quero
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "ai.h"

/*initialisation du joueur*/
void init_player(struct s_players *player, char *team,
  struct s_client * client) {
  player->invent = "";
  player->seen = "";
  player->client = client;
  player->team = team;
  player->food = 0;
  player->lvl = 1;
  player->direction = rand() % 3;
  player->X = rand() % (X_MAX - 1);
  player->Y = rand() % (Y_MAX - 1);
  player->linemate = 0;
  player->deraumere = 0;
  player->sibur = 0;
  player->mendiane = 0;
  player->phiras = 0;
  player->thystame = 0;
  player->rd = 0;
}
/*initialisation de la map*/
void init_map(struct s_map * map) {
  int i;

  i = 0;
  while (i < (Y_MAX) * (X_MAX)) {
    map[i].eat = 0;
    map[i].nbr_player = 0;
    map[i].linemate = 0;
    map[i].deraumere = 0;
    map[i].sibur = 0;
    map[i].mendiane = 0;
    map[i].phiras = 0;
    map[i].thystame = 0;
    i++;
  }
}

/*dis quelle pierre aller chercher*/
char *choose_stone(struct s_players * player, char *seen, char * inv)
{
  int i;

  i = 0;
  while (i < 6) {
    if (tab[i + 1][player->lvl - 1] > 0 &&
      find_obj(seen, (char *)stones[i]) >= 0 &&
      find_inv(inv, i + 1) < tab[i + 1][player->lvl - 1])
    {
      return (stones[i]);
    }
    i++;
  }
  return "NULL";
}

int go(struct s_players * player)
{
  if (go_obj(player, player->seen,
    choose_stone(player, player->seen, player->invent)) == -1) {
    if (player->rd > 3) {
      send_right(player->client);
      turn_right(player);
    }
    else {
      send_go(player->client);
      move(player);
    }
  }
  return 0;
}
