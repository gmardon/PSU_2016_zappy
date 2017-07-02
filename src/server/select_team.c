#include "server.h"

void handle_select_team(char *team_name, t_client *client, t_server *server)
{
  int index; 

  index = 0;
  client->team_id = -1;
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
  if (client->team_id == -1)
    {
      send_message(client, "ko\n");
      close_client(client, server);
      return ;
    }
  client->player = new_player(server, server->max_id++, client->team_id);
  send_message(client, "%i\n", get_conn_nbr(server, client->team_id));
  send_message(client, "%i %i\n", server->configuration->world_width, server->configuration->world_height);
  client->state = CLIENT_STATE_TEAM_SELECTED;
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
  return (nb);
}