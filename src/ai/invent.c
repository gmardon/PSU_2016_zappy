/*
** invent.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Mon Jun 27 10:53:12 2016 quentin quero
** Last update Mon Jun 27 10:59:07 2016 quentin quero
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

/*pose toutes les pierres du joueur*/
void lay_all(struct s_players * player) {
  int i;

  i = 0;
  while (i < 6) {
    if (find_inv(player->invent, i + 1)) {
      send_lay(player->client, stones[i]);
    }
    i++;
  }
}

/*parse le nombre de pierres et food dans inventaire / pour inventaire()*/
int find_inv(char * inventaire, int obj) {
  int i;
  int j;
  char nbr[5];
  int vir;

  vir = 0;
  j = 0;
  i = 0;
  while (inventaire[i]) {
    while (inventaire[i] && inventaire[i] >= '0' && inventaire[i] <= '9' &&
    vir == obj) {
      nbr[j] = inventaire[i];
      i++;
      j++;
    }
    if (inventaire[i] == ',') {
      vir += 1;
    }
    i++;
  }
  nbr[j] = '\0';
  if (atoi(nbr) >= 0) {
    return atoi(nbr);
  }
  return 0;
}

/*actualise nbr dans inventaire personnel*/
void inventaire(struct s_players * player, char * inventaire) {
  player->food = find_inv(inventaire, 0);
  player->linemate = find_inv(inventaire, 1);
  player->deraumere = find_inv(inventaire, 2);
  player->sibur = find_inv(inventaire, 3);
  player->mendiane = find_inv(inventaire, 4);
  player->phiras = find_inv(inventaire, 5);
  player->thystame = find_inv(inventaire, 6);
}

int all_stone(struct s_players * player) {
  int i;

  i = 0;
  while (tab[i + 1][player->lvl - 1]) {
    if (tab[i + 1][player->lvl - 1] > find_inv(player->invent, i + 1)) {
      return (-1);
    }
    i++;
  }
  return (0);
}

/*dit le nbr de joueurs present sur la case du joueur*/
int nbr_player(char *seen) {
  int    nbr, i, t, len;
  char *obj;

  i = 0;
  t = 0;
  len = 0;
  nbr = 0;
  obj = "joueur";
  while (seen[i] != ',' && seen[i]) {
    while (seen[i] == obj[t]) {
      len++; i++; t++;
      if (len == (int)strlen(obj))
        nbr += 1;
    }
    i++; len = 0; t = 0;
  }
  return nbr;
}
