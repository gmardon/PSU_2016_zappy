/*
** action_list.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Fri Jun 30 04:54:10 2017 Aurelien
** Last update Sun Jul  2 22:38:01 2017 Aurelien
*/
#include "server.h"

int		add_action(t_player *plr, char *cmd)
{
  t_alist	*tmp;
  t_alist	*new;
  int		i;

  i = 0;
  tmp = plr->action_list;
  while (tmp != NULL && tmp->next != NULL)
    {
      tmp = tmp->next;
      i++;
    }
  if (i > 10)
    return (2);
  if ((new = malloc(sizeof(t_alist))) == NULL)
    return (1);
  new->str = strdup(cmd);
  new->next = NULL;
  if (tmp == NULL)
    plr->action_list = new;
  else
    tmp->next = new;
  return (0);
}

char		*pop_action(t_player *plr)
{
  char	*ret;
  t_alist 	*tmp;

  if ((tmp = plr->action_list) == NULL)
    return (NULL);
  plr->action_list = tmp->next;
  ret = tmp->str;
  free(tmp);
  return (ret);
}
