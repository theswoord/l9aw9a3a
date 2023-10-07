#include "builtins.h"


void ft_env(t_shell *g_struct, int ac, char **av)
{
    print_env(g_struct->envlist, 0);
    g_struct->error_name = SUCCESS;
    exit_status_error(g_struct, 1);
}

// ez just use the print function from export to print all list of variables without declare -x
// even if the user puts argument just pretend to print it in the lsit and not actually add it to the list.