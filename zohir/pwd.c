#include "minishell.h"

void pwd_command(void)
{
    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL)
        ft_printf("Current Directory: %s\n");
    else
    {
        ft_printf("getcwd() error\n");
        return (1);
    }
    return (0);
}