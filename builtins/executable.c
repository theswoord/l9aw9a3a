#include "builtins.h"

char *find_executable_command(char *command, char *path)
{
    int command_len;
    char *dir_start;
    char *dir_end;
    char *executable_path;
    int path_len;

    command_len = ft_strlen(command);
    dir_start = path;
    dir_end = path;

    while (*dir_end)
    {
        while (*dir_end && *dir_end != ':')
            dir_end++;
        path_len = (dir_end - dir_start) + 1 + command_len + 1;

        executable_path = malloc(path_len);
        if (!executable_path)
        {
            printf("path allocation failed!\n");
            exit(1);
        }
        ft_memcpy(executable_path, dir_start, dir_end - dir_start);
        executable_path[dir_end - dir_start] = '/';
        ft_memcpy(executable_path + (dir_end - dir_start) + 1, command, command_len);
        executable_path[(dir_end - dir_start) + 1 + command_len] = '\0';
        // printf("%s\n", executable_path);
        // exit(1);
        if (access(executable_path, X_OK) == 0)
        {
            return (executable_path);
        }
        free(executable_path);

        if (*dir_end == ':')
        {
            dir_end++;
            dir_start = dir_end;
        }
    }
    return (NULL);
}

void execute_commands(char *command, char **args, char **env)
{
    char *path;
    char *executable_path;

    path = getenv("PATH");
    executable_path = find_executable_command(command, path);
    if (executable_path)
    {
        // add args +1 if you want to test the program with command arguments.
        int pid = fork();
        if (pid == 0)
        {
            execve(executable_path, args, env);
        }
        else
        {
            waitpid(pid, NULL, 0);
            return ;
        }
        free(executable_path);
    }
    else
        printf("bash: command not found: %s\n", command);
}

// int main(int ac, char **av, char **env)
// {
//     if (av[1])
//         execute_commands(av[1], av, env);
//     return (0);
// }