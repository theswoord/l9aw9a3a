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

void execute_commands(char *command, char **args, char **env, t_shell *g_shell)
{
    char *path;
    char *executable_path;
    int pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
            executable_path = ft_strdup(command);
        else
        {
            path = extract_from_in_list(g_shell,g_shell->envlist,"PATH");
            // path = getenv("PATH");
            executable_path = find_executable_command(command, path);
        }
        if (executable_path)
        {
            // add args +1 if you want to test the program with command arguments.
            if (access(executable_path, X_OK) == 0)
                execve(executable_path, args, env);
        }
        g_shell->error_name = COMMAND_NOT_FOUND;
        exit_status_error(g_shell);
        print_error_message(g_shell);
        exit(g_shell->exit_status);
    }
    else
    {
        // Parent process
        // Wait for the child process to complete and get its exit status
        waitpid(pid, &status, 0);

        if (WIFEXITED(status))
        {
            // Child process exited normally, retrieve its exit status
            g_shell->exit_status = WEXITSTATUS(status);
            // add_env_var(&g_shell->envlist,"?", ft_itoa(g_shell->exit_status)); // here fix
        }
    }
}

// zedt strcute l kbir hna bach ypassi l error msg
void execute_commands_pipes(char *command, char **args, char **env, t_shell *g_shell)
{
    char *path;
    char *executable_path;

    if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
        executable_path = ft_strdup(command);
    else
    {
        path = getenv("PATH");
        executable_path = find_executable_command(command, path);
    }
    if (executable_path)
    {
        // add args +1 if you want to test the program with command arguments.
        if (access(executable_path, X_OK) == 0)
            execve(executable_path, args, env);
    }
    // print to fd 2 instead of fd 1
    g_shell->error_name = COMMAND_NOT_FOUND;
    exit_status_error(g_shell);
    print_error_message(g_shell);
    return;
}
