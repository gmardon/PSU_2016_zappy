#include "server.h"

t_configuration *parseArgs(int argc, char *argv[])
{
    t_configuration *config;
    int	opt;
    int	index;

    opterr = 0;
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
                config->initial_client_per_team = atoi(optarg);
            else if (opt == 't')
                config->temporal_delay = atof(optarg);
            else if (opt == 's')
                config->seed = atoi(optarg);
            //else if (c == 'n')
            //    config->teamNames = GetTeamsFromArg(optarg);
        }
    for (index = optind; index < argc; index++)
        printf("Non-option argument %s\n", argv[index]);
    return config;
}