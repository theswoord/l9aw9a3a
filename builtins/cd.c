#include "builtins.h"

// make a function that finds the path based on key name in the enviroment.
// replace old with current pwd
// replace current pwd in env with current pwd with getcwd

t_var_t *find_value(char *key, t_var_t *head, char *value)
{
    t_var_t *current;

    current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = ft_strdup(value);
            return (current);
        }
        current = current->next;
    }
    return NULL;
}

char *find_key(char *key, t_var_t *head)
{
    t_var_t *current;

    current = head;
    while (current != NULL)
    {
        if (ft_strcmp(current->key, key) == 0)
        {
            return (current->value);
        }
        current = current->next;
    }
    return NULL;
}

void change_pwd(t_var_t *head, t_shell *g_shell)
{
    t_var_t *old_pwd;
    t_var_t *current_pwd;
    char pwd[1024];

    getcwd(pwd, sizeof(pwd));
    find_value("OLDPWD", head, find_key("PWD", head));
    find_value("PWD", head, pwd);
    if (old_pwd == NULL || current_pwd == NULL)
    {
        g_shell->error_name = HOME_NOT_SET;
        exit_status_error(g_shell, 1);
        print_error_message(g_shell);
        // exit(1);
    }
}

void cd_command(char *directory, char **env, t_shell *g_shell)
{
    if (!directory)
        chdir(extract_from_in_list(g_shell,g_shell->envlist,"PATH"));
    else if (chdir(directory) != 0)
    {
        g_shell->error_name = PERMISSION_DENIED_FILE;
        exit_status_error(g_shell, 1);
        print_error_message(g_shell);
        return;
    }
    // enviroment can be changed anytime.
    change_pwd(g_shell->envlist, g_shell);
    g_shell->error_name = SUCCESS;
    exit_status_error(g_shell, 1);
    return;
}
