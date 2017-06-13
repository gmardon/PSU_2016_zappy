#include "zappy.h"

void my_error(char *msg, int exit_code)
{
	printf("%s\n", msg);
	if (exit_code != 0)
		exit(exit_code);
}