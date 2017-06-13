#include "server.h"

int main(int argc, char *argv[])
{
    t_configuration *config;
    t_server *server;

    config = parse_args(argc, argv);
	server = create_server(config);
    
	return (0);
}