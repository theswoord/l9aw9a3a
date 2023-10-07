#include "builtins.h"

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
        error_set(g_shell, HOME_NOT_SET, 1);
    }
}

void cd_command(char *directory, char **env, t_shell *g_shell)
{
    if (!directory)
        chdir(getenv("HOME"));
    else if (chdir(directory) != 0)
    {
        error_set(g_shell, PERMISSION_DENIED_FILE, 1);
        return;
    }
    // enviroment can be changed anytime.
    change_pwd(g_shell->envlist, g_shell);
    error_set(g_shell, SUCCESS, 0);
    return;
}
