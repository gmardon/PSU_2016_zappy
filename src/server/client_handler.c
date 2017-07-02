#include "server.h"

void handle_client_message(char *message, t_client *client, t_server *server)
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