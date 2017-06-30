/*
** ia.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:26:35 2017 Julien Nabti
** Last update Fri Jun 30 17:26:47 2017 Julien Nabti
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

int X_MAX = 10;
int Y_MAX = 10;

char  read_buffer[512];
char  *vision_str = NULL;
char  *stuff_str = NULL;

pthread_mutex_t vision_mutex;
pthread_mutex_t vision_mutex2;
pthread_mutex_t stuff_mutex;
pthread_mutex_t stuff_mutex2;

const int tab[7][8] = {
  {1, 2, 2, 4, 4, 6, 6},  // nbr need players
  {1, 1, 2, 1, 1, 1, 2},  // linemate
  {0, 1, 0, 1, 2, 2, 2},  // deraumere
  {0, 1, 1, 2, 1, 3, 2},  // sibur
  {0, 0, 0, 0, 3, 0, 2},  // mendiane
  {0, 0, 2, 1, 0, 1, 2},  // phiras
  {0, 0, 0, 0, 0, 0, 1}}; // thystame

char stones[7][10] = {
  {"linemate"},
  {"deraumere"},
  {"sibur"},
  {"mendiane"},
  {"phiras"},
  {"thystame"}};

void receve_see(struct s_players * player)
{
  send_see(player->client);

  pthread_mutex_lock(&vision_mutex);
  if (vision_str != NULL) {
  player->seen = strdup(vision_str);
  }
}

void receve_stuff(struct s_players * player)
{
  send_stuff(player->client);

  pthread_mutex_lock(&stuff_mutex);
  if (stuff_str != NULL) {
    player->invent = strdup(stuff_str);
  }
}

void move_alea(struct s_players * player)
{
  if (player->rd > 1) {
    send_go(player->client);
  }
  else
  send_left(player->client);
}

/*algo de IA*/
void algo(struct s_players * player) {
    player->rd = rand() % 5;
    receve_stuff(player);
    player->invent = player->invent;
    receve_see(player);
    player->seen = player->seen;
    inventaire(player, player->invent);
    if (player->food < 5) {
      if (go_obj(player, player->seen, "nourriture") == -1) {
        move_alea(player);
      }
      printf("%s\n", "go chercher food"); }
    else if (all_stone(player)) {
      printf("%s\n", "go chercher pierres");
      go(player);
    }
    else if (nbr_player(player->seen) < tab[0][player->lvl - 1]) {
      //appelle les joueurs du meme niveau
      printf("%s\n", "go chercher joueurs");
    }
    else
    {
      lay_all(player);
      send_incantation(player->client);
      printf("%s\n", "EVOLUTIONNNNN");
    }
}

void  add_to_recvs()
{
  printf("----receve :%s\n", read_buffer);
  if (strncmp(read_buffer, "{ ", 2) == 0)
    {
      if (vision_str)
        free(vision_str);
      vision_str = strdup(read_buffer);
      pthread_mutex_unlock(&vision_mutex);
    }
  else if (strncmp(read_buffer, "{", 1) == 0)
  {
    if (stuff_str)
      free(stuff_str);
    stuff_str = strdup(read_buffer);
    pthread_mutex_unlock(&stuff_mutex);
  }
}

void	*check(void *client)
{
  int   rc;
  while (((t_client *)client)->end == 0)
  {
    rc = read(((t_client *)client)->fd, read_buffer, 199);
    if (rc < 0)
      break;
    read_buffer[rc] = '\0';
    write(1, read_buffer, rc);
    if (strcmp(read_buffer, "mort") == 0)
      {
	((t_client *)client)->end = 1;
	add_to_recvs();
      }
  }
  pthread_exit((void *)client);
}

int	ia(struct s_client *client)
{
  pthread_t listen_thread;
  void      *res;
  struct s_players * player;
  srand(time(NULL));
  pthread_mutex_lock(&vision_mutex);
  pthread_mutex_lock(&stuff_mutex);

  player = malloc(sizeof(struct s_players));

  init_player(player, client->options->team, client);
  pthread_create(&listen_thread, NULL, &check, (void *)client);
  while (1)
  {
    algo(player);
    sleep(1);
    if (client->end == 1)
      pthread_join(listen_thread, &res);
  }
  free(player);
  (void)res;
  return (0);
}
