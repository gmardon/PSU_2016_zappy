#include "server.h"

void handle_select_team(char *team_name,
t_client *client, t_server *server)
{
  client->team_id = -1;
  handle_select_find(client, server, team_name);
  if (client->team_id == GRAPHIC)
  {
    handle_select_graph(server, client);
    return ;
  }
  else if (client->team_id == -1)
    {
      send_message(client, "ko\n");
      close_client(client, server);
      return ;
    }
  client->player = new_player(server, server->max_id++, client->team_id);
  send_message(client, "%i\n%i %i\n", get_conn_nbr(server, client->team_id),
  server->configuration->world_width, server->configuration->world_height);
  client->state = CLIENT_STATE_TEAM_SELECTED;
}

void handle_select_find(t_client *client,
t_server *server, char *team_name)
{
  int index; 

  index = 0;
  while (server->configuration->teams[index])
  {
    printf("in while : %s\n", server->configuration->teams[index]);
    if (strcmp(team_name, server->configuration->teams[index]) == 0)
    {
      printf("matched : %s\n", server->configuration->teams[index]);
      client->team_id = index;
      break;
    }
    index++;
  }
  if (client->team_id == -1 && strstr(team_name, "GRAPHIC") != NULL)
    client->team_id = GRAPHIC;
}

void handle_select_graph(t_server *serv, t_client *cl)
{
  cl->state = CLIENT_STATE_TEAM_SELECTED;
  cl->player = NULL;
  msz_evnt(serv);
  sgt_evnt(serv);
  mct_evnt(serv);
  all_tna_evnt(serv);
  all_pnw_evnt(serv);
  all_enw_evnt(serv);
}

int get_conn_nbr(t_server *serv, int team_id)
{
  t_egg_list *tmp;
  t_clist *tmpp;
  int nb;

  nb = serv->configuration->client_per_team;
  tmp = serv->game->egg;
  while (tmp != NULL)
  {
    if (tmp->team_id == team_id
        && tmp->hatch_time <= 0)
        nb++;
    tmp = tmp->next;
  }
  tmpp = serv->client_list;
  while (tmpp != NULL)
  {
    if (tmpp->client->player != NULL
     && tmpp->client->team_id == team_id)
      nb--;
    tmpp = tmpp->next;
  }
  if (nb < 0)
    return (0);
  return (nb);
}

char *get_team_by_id(t_server *serv, int id)
{
  int i;
  char *ret;

  i = 0;
  ret = NULL;
  while (serv->configuration->teams[i])
  {
    if (i == id)
    {
      ret = serv->configuration->teams[i];
      break;
    }
    i++;
  }
  return (ret);
}