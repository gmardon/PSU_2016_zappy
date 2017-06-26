#include "server.h"

void handle_select_team(char *team_name, t_client *client, t_server *server)
{
    if (strcmp(team_name, server->configuration->team1_name) == 0)
    {
        client->team_id = 1;
    }
    else if (strcmp(team_name, server->configuration->team2_name) == 0)
    {
        client->team_id = 2;
    }
    else
    {
        send_message(client, "ko\n");
        close_client(client, server);
        return;
    }
    //send_message(client, "%i\n", client->id);
    send_message(client, "%i %i\n", server->configuration->world_width, server->configuration->world_height);
    client->state = CLIENT_STATE_TEAM_SELECTED;
}