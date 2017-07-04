/*
** main.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 22:51:29 2017 Aurelien
** Last update Sun Jul  2 22:51:33 2017 Aurelien
*/
#include "server.h"

int			main(int argc, char *argv[])
{
  t_configuration	*config;
  t_server		*server;

  config = parse_args(argc, argv);
  server = create_server(config);
  start_server(server);
  del_server(server);
  return (0);
}

void		del_server(t_server *serv)
{
  t_clist	*tmp;
  int		i;

  tmp = serv->client_list;
  while (tmp != NULL)
    {
      close_client(tmp->client, serv);
      tmp = tmp->next;
    }
  check_del_cl(serv);
  del_game(serv);
  i = 0;
  while (serv->configuration->teams[i])
    {
      free(serv->configuration->teams[i]);
      i++;
    }
  free(serv->configuration->teams);
  free(serv->configuration);
  free(serv);
}

void		del_game(t_server *serv)
{
  int		i;

  i = 0;
  while (i < serv->game->width)
    {
      free(serv->game->map[i]);
      i++;
    }
  while (serv->game->egg != NULL)
    del_egg(serv, serv->game->egg);
  while (serv->game->resp != NULL)
    del_resp(serv->game, serv->game->resp);
  free(serv->game->map);
  free(serv->game);
  serv->game = NULL;
}

int fork_cmd_chk(t_server *serv, t_player *plr, char *cmd)
{
  if (cmd)
    pfk_evnt(serv, plr);
  return (0);
}

int	pdi_evnt(t_server *serv, t_player *plr)
{
  char	*ret;

  if ((ret = malloc(sizeof(char) * 111)) == NULL)
    return (1);
  sprintf(ret, "pdi %d\n", plr->id);
  add_resp(serv->game, ret, GRAPHIC);
  free(ret);
  return (0);
}
