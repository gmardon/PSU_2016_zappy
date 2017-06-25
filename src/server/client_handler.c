#include "server.h"

void handle_client_message(char *message, t_client *client, t_server *server)
{
    if (client->state == CLIENT_STATE_CONNECTED)
        send_select_team(message, client, server);
    //if (client->state == CLIENT_STATE_TEAM_SELECTED)
    //    send_select_team(message, client, server);
}