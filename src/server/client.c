#include "server.h"

void send_message(t_client *client, char *msg, ...)
{
    char *content;
    int len;
    va_list args;

    if (client->fd)
    {
        va_start(args, msg);
        len = vasprintf(&content, strdup(msg), args);
        printf("< %s", content);
        write(client->fd, content, len);
        va_end(args);
    }
}

void close_client(t_client *client)
{
    if (client->fd != -1)
        close(client->fd);

    client->fd = 0;
    printf("Client disconnected <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
}

void send_select_team(char *team_name, t_client *client, t_server *server)
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
        close_client(client);
        return;
    }
    send_message(client, "%i %i\n", server->configuration->world_width, server->configuration->world_height);
}

void handle_client(t_client *client)
{
    char *buffer;

    printf("New client connected from <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
    send_message(client, "WELCOME\n");
}

void handle_client_message(t_client *client, char *message)
{
}