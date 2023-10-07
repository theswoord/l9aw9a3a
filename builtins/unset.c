#include "builtins.h"

void	unset_var_env(t_var_t **head, char *key)
{
	t_var_t	*current;
	t_var_t	*previous;

	current = *head;
	previous = NULL;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (previous == NULL)
				*head = current->next;
			else
				previous->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(int ac, char **av, t_shell *g_struct)
{
	int	i;

	i = 0;
	while (++i < ac)
		unset_var_env(&g_struct->envlist, av[i]);
	return ;
}
