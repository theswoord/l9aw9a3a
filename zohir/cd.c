#include "builtins.h"

void cd_command(int ac, char **av)
{
    if (chdir(av[1]) != 0)
        return;
}