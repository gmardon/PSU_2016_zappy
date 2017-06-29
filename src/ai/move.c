/*
** move.c for PSU_2015_zappy in /home/quentin/Dropbox/progra/tek2/Projets_C/PSU_2015_zappy/client/IA/src
**
** Made by quentin quero
** Login   <quentin@epitech.net>
**
** Started on  Tue Jun 14 16:28:27 2016 quentin quero
** Last update Fri Jun 17 10:43:05 2016 quentin quero
*/

#include <stdlib.h>
#include <string.h>

#include "ai.h"

/*
int move_fwd(struct s_client *client, char *cmd)
{
  int rc;

  (void)cmd;
  rc = send(client->fd, "fwd", 3, MSG_DONTWAIT);
  if (rc == -1)
    return (-1);
  return (0);
}

int move_fwd(struct s_client *client, char *cmd)
{
  int rc;

  rc = send(client->fd, "fwd", 3, MSG_DONTWAIT);
  if (rc == -1)
    return (-1);
  return (0);
}
*/

void move_up(struct s_players * players) {
  if (players->Y == 0) {
    players->Y = Y_MAX - 1;
  }
  else
  {
    players->Y -= 1;
  }
}

void move_down(struct s_players * players) {
  if (players->Y == Y_MAX - 1) {
    players->Y = 0;
  }
  else
  {
    players->Y += 1;
  }
}

void move_right(struct s_players * players) {
  if (players->X == X_MAX - 1) {
    players->X = 0;
  }
  else
  {
    players->X += 1;
  }
}


void move_left(struct s_players * players) {
  if (players->X == 0) {
    players->X = X_MAX - 1;
  }
  else
  {
    players->X -= 1;
  }
}

// rotation:  0 = haut,  1 = droite,  2 = bas,  3 = gauche

void turn_left(struct s_players * players) {
  if (players->direction == 0) {
    players->direction = 3;
  }
  else
    players->direction -= 1;
}

void turn_right(struct s_players * players) {
  if (players->direction == 3) {
    players->direction = 0;
  }
  else
    players->direction += 1;
}

void move(struct s_players * players) {
  if (players->direction == 0) {
    move_up(players);
  }
  if (players->direction == 1) {
    move_right(players);
  }
  if (players->direction == 2) {
    move_down(players);
  }
  if (players->direction == 3) {
    move_left(players);
  }
}

// direction:   0 = gauche,    1 = droite ,    2 = avancer

void move_player(struct s_players * players, int direction) {
  if (direction == 0) {
    turn_left(players);
  }
  else if (direction == 1)
  {
    turn_right(players);
  }
  else if (direction == 3)
  {
    move(players);
  }
}
