/*
** client_handler.c for zappy in /home/aurelien/home/aurelien.olibe/delivery/PSU_2016_zappy/src/server
**
** Made by Aurelien
** Login   <aurelien.olibe@epitech.eu@epitech.net>
**
** Started on  Sun Jul  2 22:42:44 2017 Aurelien
** Last update Sun Jul  2 22:43:19 2017 Aurelien
*/
#include "server.h"

void handle_client_message(char *message,
			   t_client *client, t_server *server)
{
  if (client->state == CLIENT_STATE_CONNECTED)
    handle_select_team(message, client, server);
  else if (client->state == CLIENT_STATE_TEAM_SELECTED)
    {
      if (client->team_id == GRAPHIC)
	handle_graph(server, client, message);
      else
	handle_cmd(server, client, message);
    }
}
