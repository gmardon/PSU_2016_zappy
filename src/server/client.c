#include "server.h"

void send_message(t_client *client, char *msg, ...)
{
    char *content;
    int len;
    va_list args;

    content = my_malloc(40960);
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
        //del_client(server, client->fd);
        close(client->fd);
    }
    client->fd = 0;
    printf("Client disconnected <%s:%d>\n", get_client_addr(client->in), get_client_port(client->in));
}

int check_del_cl(t_server *serv)
{
    int count;

    count = 0;
    while (del_client(serv, 0))
        count++;
    return (count);
}