#include "server.h"

void handle_select_team(char *team_name, t_client *client, t_server *server)
{
  int index; 

  index = 0;
  client->team_id = -1;
  while (server->configuration->teams[index])
  {
    if (strcmp(team_name, server->configuration->teams[index]) == 0)
    {
      client->team_id = index;
    }
    index++;
  }
  if (client->team_id == -1)
    {
      send_message(client, "ko\n");
      close_client(client, server);
      return;
    }
    //send_message(client, "%i\n", client->id);
    send_message(client, "%i %i\n", server->configuration->world_width, server->configuration->world_height);
    client->state = CLIENT_STATE_TEAM_SELECTED;
}
