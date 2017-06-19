#include "ai.h"

void validate_configuration(t_configuration *config)
{
  if (config->machine == NULL)
    config->machine = "localhost";
  if (config->name != NULL)
    my_error("Invalid name, must be fill with team name.", -1);
  if (config->port < 1000)
    my_error("Unable to bind socket. Ports under 1000 are reserved.", -1);
}

t_configuration *parse_args(int argc, char *argv[])
{
    t_configuration *config;
    int	opt;

    config = my_malloc(sizeof(t_configuration));
    while ((opt = getopt (argc, argv, "p:n:h:")) != -1)
        {
            if (opt == 'p')
                config->port = atoi(optarg);
            else if (opt == 'n')
                config->name = strdup(optarg);
            else if (opt == 'h')
                config->machine = strdup(optarg);
        }
    validate_configuration(config);
    return (config);
}