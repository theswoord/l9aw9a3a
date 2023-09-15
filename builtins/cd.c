#include "builtins.h"

// make a function that finds the path based on key name in the enviroment.
// replace old with current pwd
// replace current pwd in env with current pwd with getcwd

t_var_t *find_value(char *key, t_var_t *head)
{
    t_var_t *current;

    current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            return (current);
        }
        current = current->next;
    }
    return NULL;
}

void change_pwd(t_var_t *head)
{
    t_var_t *old_pwd;
    t_var_t *current_pwd;
    char pwd[1024];

    getcwd(pwd, sizeof(pwd));
    old_pwd = find_value("OLDPWD", head);
    printf("%s=%s\n", old_pwd->key,old_pwd->value);
    current_pwd = find_value("PWD", head);
    printf("%s=%s\n", current_pwd->key, current_pwd->value);
    if (old_pwd == NULL || current_pwd == NULL)
    {
        perror("enviroment variable not found.");
        exit(1);
    }
    if (old_pwd->value)
        free(old_pwd->value);
    old_pwd->value = ft_strdup(current_pwd->value);
    if (current_pwd->value)
        free(current_pwd->value);
    current_pwd->value = ft_strdup(pwd);
}

void cd_command(int ac, char *directory, char **env, t_shell *g_struct)
{
    pid_t pid;

    char *pwd;
    // pwd = find_value("PWD", g_struct->envlist);
    pid = fork();
    if (pid == 0)
    {
        if (ac != 2)
        {
            perror("Usage: <directory>");
            exit(1);
        }
    pwd = getenv("PWD");
    pwd = ft_strjoin(pwd, "/");

    pwd = ft_strjoin(pwd, directory);
    printf("%s|\n",pwd);
        if (chdir(pwd) != 0)
        {
            perror("chdir");
            exit(1);
        }
        // enviroment can be changed anytime.
        change_pwd(g_struct->envlist);
        // exit(0);    
        }
    else if (pid > 0)
    {
        waitpid(pid, NULL, 0);
        return;
    }
    else
    {
        perror("fork");
        exit(1);
    }
}