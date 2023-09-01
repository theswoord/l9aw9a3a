#include "builtins.h"

env_var_t *global_enviroment;

void add_env_var(env_var_t **head, char *key, char *value)
{
	env_var_t *new_node;
	env_var_t *current;

	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			if (ft_strcmp(current->value, value) != 0)
			{
				free(current->value);
				current->value = ft_strdup(value);
			}
			return;
		}
		current = current->next;
	}
	new_node = malloc(sizeof(env_var_t));
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = *head;
	*head = new_node;
}

void initialize_environment(env_var_t **head, char **env)
{
	char *key;
	char *value;
	int i;
	*head = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_charfind(env[i], '=') != 0)
		{
			key = ft_substr(env[i], 0, ft_charfind(env[i], '='));
			value = ft_strchr(env[i], '=') + 1;
			add_env_var(head, key, value);
			free(key);
		}
		i++;
	}
}

void free_env(env_var_t *head)
{
	env_var_t *current;
	env_var_t *temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->key);
		free(temp->value);
		free(temp);
	}
}

void print_env(env_var_t *head, int bool)
{
	env_var_t *current = head;

	while (current != NULL)
	{
		if (bool == 1)
		{
			if (!(current->value))
				printf("declare -x %s\n", current->key);
			else
				printf("declare -x %s=\"%s\"\n", current->key, current->value);
		}
		else
		{
			if (!(current->value))
				printf("%s\n", current->key);
			else
				printf("%s=\"%s\"\n", current->key, current->value);
		}
		current = current->next;
	}
}

void add_to_env(char *argument, env_var_t **env)
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

void export(int ac, char **av, char **env)
{
	int i;

	initialize_environment(&global_enviroment, env);
	i = 0;
	while (++i < ac)
		add_to_env(av[i], &global_enviroment);
	print_env(global_enviroment, 1);
	return;
}

// int main(int ac, char **av, char **env)
// {
// 	export(ac, av, env);
// 	return (0);
// }

// after finishing the export command we need to seperate the command and the creation of global_enviroment list
// cuz export only adds or modifies enviroment variables