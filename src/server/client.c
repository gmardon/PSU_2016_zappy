#include "server.h"

void send_message(t_client *client, char *msg, ...)
{
    char *content;
    int len;
    va_list args;

    content = my_malloc(256);
    if (client->fd)
    {
        va_start(args, msg);
        len = vsprintf(content, strdup(msg), args);
        printf("> %s", content);
        write(client->fd, content, len);
        va_end(args);
    }
}

void close_client(t_client *client, t_server *server)
{
    if (client->fd > 0)
    {
        FD_CLR(client->fd, &server->master);
        close(client->fd);
    }
    client->fd = 0;
    printf("Client disconnected <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
}

void send_select_team(char *team_name, t_client *client, t_server *server)
{
    printf("teamname: '%s'\n", team_name);
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
    send_message(client, "%i %i\n", server->configuration->world_width, server->configuration->world_height);
    client->state = CLIENT_STATE_TEAM_SELECTED;
}

void handle_client(t_client *client)
{
    printf("New client connected from <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\n");
}

void handle_client_message(char *message, t_client *client, t_server *server)
{
    if (client->state == CLIENT_STATE_CONNECTED)
        send_select_team(message, client, server);
}