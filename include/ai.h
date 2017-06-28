#ifndef _AI_H_
#define _AI_H_ 
#include "zappy.h"

typedef struct s_configuration
{
    int				port;
    char*			name;
    char*			machine;
}				t_configuration;

t_configuration *parse_args(int argc, char *argv[]);
#endif