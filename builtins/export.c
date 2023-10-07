#include "builtins.h"

void add_to_environ(char *argument, t_var_t **env)
{
	int i;
	char *key;
	char *value;

	if (!argument || *argument == '\0')
		return;
	if (ft_charfind(argument, '=') != 0)
	{
		key = ft_substr(argument, 0, ft_charfind(argument, '='));
		value = ft_strchr(argument, '=') + 1;
	}
	else
	{
		key = ft_strdup(argument);
		value = NULL;
	}
	add_env_var(env, key, value);
	free(key);
}

void export(t_shell *g_struct, int ac, char **av, char **env)
{
	int i;

	i = 0;
	while (++i < ac)
		add_to_environ(av[i], &g_struct->envlist);
	if (ac == 1)
		print_env(g_struct->envlist, 1);
}
