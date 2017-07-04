/*
** game.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/game
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Wed Jun 21 23:08:35 2017 Aurelien
** Last update Sun Jul  2 23:32:31 2017 Aurelien
*/
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "server.h"

int		check_game_finish(t_server *serv)
{
  t_clist	*tmp;
  int		nb;

  tmp = serv->client_list;
  while (tmp != NULL)
    {
      if (tmp->client->player != NULL
	  && tmp->client->player->lvl >= MAX_LVL)
        {
	  nb = look_for_same_lvl(serv,
				 tmp->client->team_id,
				 tmp->client->player->lvl);
	  if (nb >= 6)
            {
	      printf("The Team %s have WIN !!!\n",
		     serv->configuration->teams[tmp->client->team_id]);
	      return (0);
            }
        }
      tmp = tmp->next;
    }
  return (1);
}

int		look_for_same_lvl(t_server *serv, int team_id, int lvl)
{
  t_clist	*tmp;
  int		nb;

  tmp = serv->client_list;
  nb = 0;
  while (tmp != NULL)
    {
      if (tmp->client->team_id == team_id
	  && tmp->client->player->lvl == lvl)
	nb++;
      tmp = tmp->next;
    }
  return (nb);
}

int		do_one_cycle(t_server *serv)
{
  t_clist	*tmp;
  t_player	*player;

  tmp = serv->client_list;
  while (tmp != NULL)
    {
      if ((player = tmp->client->player) == NULL)
        {
	  tmp = tmp->next;
	  continue;
        }
      cycle_gest(serv, player, tmp);
      tmp = tmp->next;
    }
  do_one_cycle_egg(serv);
  return (0);
}

int		do_one_cycle_egg(t_server *serv)
{
  t_egg_list	*tmp;

  tmp = serv->game->egg;
  while (tmp != NULL)
    {
      if (tmp->hatch_time > 0)
        {
	  tmp->hatch_time -= 1;
	  if (tmp->hatch_time == 0)
	    eht_evnt(serv, tmp);
        }
      tmp = tmp->next;
    }
  return (0);
}

int			calc_elapsed(double unit)
{
  static char		bool_old_set = 0;
  static struct timeval	old_tv = {0, 0};
  struct timeval	tv;
  struct timeval	elapsed;

  if (bool_old_set == 0)
    {
      gettimeofday(&old_tv, NULL);
      bool_old_set = 1;
      return (0);
    }
  gettimeofday(&tv, NULL);
  if ((elapsed.tv_sec = tv.tv_sec - old_tv.tv_sec) > 0
      && elapsed.tv_sec--)
    elapsed.tv_usec = tv.tv_usec + (1000000 - old_tv.tv_usec);
  else if (tv.tv_sec - old_tv.tv_sec == 0)
    elapsed.tv_usec = tv.tv_usec - old_tv.tv_usec;
  if (elapsed.tv_usec > unit
      || elapsed.tv_sec > 0)
    {
      gettimeofday(&old_tv, NULL);
      return (1);
    }
  return (0);
}
