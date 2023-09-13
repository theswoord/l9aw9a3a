#include "builtins.h"

void cd_command(int ac, char **av)
{
    pid_t pid;
    
    pid = fork();
    if (pid == 0)
    {
        if (ac != 2)
        {
            perror("Usage: <directory>");
            exit(1);
        }
        if (chdir(av[1]) != 0)
        {
            perror("chdir");
            exit(1);
        }
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
