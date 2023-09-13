#include "builtins.h"

void    ft_env(int ac, char **av)
{
    print_env(g_struct, 0);
}

// ez just use the print function from export to print all list of variables without declare -x
// even if the user puts argument just pretend to print it in the lsit and not actually add it to the list.