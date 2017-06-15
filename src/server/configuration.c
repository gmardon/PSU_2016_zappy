#include "server.h"

void validate_configuration(t_configuration *config)
{
  if (config->client_per_team < 1)
    my_error("Initial available slots per team must be at least 1.", -1);
  if (config->world_height < 4 || config->world_width < 4)
    my_error("Invalid requested map size. A map should be a least 5x5.", -1);
  if (config->port < 1000)
    my_error("Unable to bind socket. Ports under 1000 are reserved.", -1);
  if (config->port > 65535)
    my_error("Illegal port number.", -1);
  //if (config->teamNames == NULL ||
   //   config->teamNames->countLinkedList(config->teamNames) > 1)
   // Log(ERROR, "You must provide as least 1 team name.");
  if (config->temporal_delay < 0)
    my_error("Temporal factor must be > 0.", -1);
}

t_configuration *parse_args(int argc, char *argv[])
{
    t_configuration *config;
    int	opt;

    config = my_malloc(sizeof(t_configuration));
    while ((opt = getopt (argc, argv, "p:x:y:c:t:n:s:")) != -1)
        {
            if (opt == 'p')
                config->port = atoi(optarg);
            else if (opt == 'x')
                config->world_width = atoi(optarg);
            else if (opt == 'y')
                config->world_height = atoi(optarg);
            else if (opt == 'c')
                config->client_per_team = atoi(optarg);
            else if (opt == 't')
                config->temporal_delay = atof(optarg);
            else if (opt == 's')
                config->seed = atoi(optarg);
            else if (opt == 'n') 
            {
                config->team1_name = strdup(optarg);
                config->team2_name = strdup(argv[optind]);
            }
        }
    validate_configuration(config);
    return (config);
}