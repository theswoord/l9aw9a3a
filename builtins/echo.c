#include "builtins.h"

void echo_command(int ac, char **av)
{
    pid_t pid;
    int i;
    int skip_newline;

    pid = fork();
    if (pid == 0)
    {
        i = skip_newline = 0;

        if (ac > 1 && ft_strncmp(av[1], "-n", 2) == 0)
            skip_newline = 1;
        i = skip_newline + 1;

        while (i < ac)
        {
            printf("%s", av[i]);
            if (i < ac - 1)
                printf(" ");
            i++;
        }
        if (!skip_newline)
            printf("\n");

        exit(0);
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
}

// int main(int argc, char **argv)
// {
//     echo_command(argc, argv);
//     return 0;
// }