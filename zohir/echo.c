#include "builtins.h"

void echo_command(int ac, char **av)
{
    int i;
    int skip_newline;

    if (ac > 1 && ft_strncmp(av[1], "-n", 2) == 0)
        skip_newline = 1;
    i = skip_newline + 1;
    while (i < ac)
    {
        ft_printf("%s", av[i]);
        if (i < ac - 1)
            printf(" ");
        i++;
    }
    if (!skip_newline)
        ft_printf("\n");
}