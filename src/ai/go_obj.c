/*
** go_obj.c for  in /home/julienN/PSU_2016_zappy/src/ai
** 
** Made by Julien Nabti
** Login   <julienN@epitech.net>
** 
** Started on  Fri Jun 30 17:28:26 2017 Julien Nabti
** Last update Fri Jun 30 17:47:58 2017 Julien Nabti
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

/*return lla distance en etage pour find_obj*/
int	find_floor(int nbr)
{
  int floor;
  int total;

  total = 0;
  floor = 0;
  while (total <= nbr)
    {
      total += (2 * floor) + 1;
      floor++;
    }
  return (floor - 1);
}

/*return si c'est a gauche, tout droit, ou a droite pour find_obj*/
int	find_right_left(int nbr)
{
  int floor;

  floor = find_floor(nbr);
  if (find_floor(nbr - floor) < find_floor(nbr))
    {
      return (-1);
    }
  else if (find_floor(nbr + floor) > find_floor(nbr))
    {
      return (1);
    }
  return (0);
}

/*trouve l'objet demande*/
int	find_obj(char *seen, char *obj)
{
  int    pos, stop, i, t, len;
  
  i = 0;
  t = 0;
  len = 0;
  pos = 0;
  stop = 0;
  while (seen[i])
    {
      if (seen[i] == ',' && stop == 0)
	pos++;
      while (seen[i] && obj[t] && seen[i] == obj[t])
	{
	  len++;
	  i++;
	  if (len + 1 == (int)strlen(obj))
	    {
	      stop = 1;
	    }
	  t++;
	}
      i++;
      len = 0;
      t = 0;
    }
  if (stop == 1)
    {
      return (pos);
    }
  return (-1);
}

/*va sur l'objet demande si il est dans la vision*/
int	go_obj(struct s_players * player, char *seen, char *obj)
{
  int front, cote;
  
  front = find_floor(find_obj(seen, obj));
  cote = find_right_left(find_obj(seen, obj));
  if (find_obj(seen, obj) != -1)
    {
    while (front > 0)
      {
	send_go(player->client);
	front--;
	printf("%s\n", "--avance");
      }
    if (cote == -1)
      {
	printf("%s\n", "--gauche");
	send_left(player->client);
	receve_see(player);
	return (go_obj(player, player->seen, obj), 1);
      }
    else if (cote == 1)
      {
	printf("%s\n", "--droite");
	send_right(player->client);
	receve_see(player);
	return (go_obj(player, player->seen, obj), 1);
      }
    else if (front == 0)
      {
	printf("--take : %s\n", obj);
	return (send_take(player->client, obj), 1);
      }
    }
  return (-1);
}
