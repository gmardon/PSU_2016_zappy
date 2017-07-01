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
  if (config->teams == NULL)
   my_error("You must provide as least 1 team name.", -1);
  if (config->frequency < 0)
    my_error("Frequency must be > 0.", -1);
}

char **parse_teams(char *first_team, int argc, char *argv[])
{
    int index;
    char **teams;

    teams = my_malloc(((argc - optind) + 2) * sizeof(char*));
    if (first_team)
    {
        index = 0;
        teams[0] = first_team;
        while ((optind + index) < argc && argv[optind + index] != NULL)
        {
            teams[index + 1] = strdup(argv[optind + index]);
            index++;
        }
        teams[index] = 0;
    }
    return (teams);
}

t_configuration *init_configuration()
{
    t_configuration *config;

    config = my_malloc(sizeof(t_configuration));
    config->port = 4242;
    config->frequency = 100;
    config->world_width = 42;
    config->world_height = 42;
    return (config);
}

t_configuration *parse_args(int argc, char *argv[])
{
    t_configuration *config;
    int	opt;
    char *first_team;

    config = init_configuration();
    while ((opt = getopt (argc, argv, "p:x:y:c:f:n:s:")) != -1)
        {
            if (opt == 'p')
                config->port = atoi(optarg);
            else if (opt == 'x')
                config->world_width = atoi(optarg);
            else if (opt == 'y')
                config->world_height = atoi(optarg);
            else if (opt == 'c')
                config->client_per_team = atoi(optarg);
            else if (opt == 'f')
                config->frequency = atof(optarg);
            else if (opt == 's')
                config->seed = atoi(optarg);
            else if (opt == 'n') 
                first_team = strdup(optarg);
        }
    config->teams = parse_teams(first_team, argc, argv);
    validate_configuration(config);
    return (config);
}