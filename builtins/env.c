#include "builtins.h"

void ft_env(t_shell *g_struct, int ac, char **av)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
    {
        // print_env(g_struct, 0);
        print_env(g_struct->envlist,0);
    }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
        exit(0);
    }
    else
    {
        perror("fork");
        exit(1);
    }
    g_struct->exit_status = 0;
}

// ez just use the print function from export to print all list of variables without declare -x
// even if the user puts argument just pretend to print it in the lsit and not actually add it to the list.