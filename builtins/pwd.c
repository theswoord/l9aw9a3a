#include "builtins.h"

void pwd_command(void)
{
    pid_t pid;

    pid = fork();
    if (pid == 0)
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