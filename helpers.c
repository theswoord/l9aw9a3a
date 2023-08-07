#include "minishell.h"

int ft_charfind(const char *str, char c)
{
	int i;

 	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (0);
}


int ft_strcmp(const char *s1, const char *s2)
{
    while (*s1 && (*s1 == *s2)) {
        s1++;
        s2++;
    }
    return *(unsigned char*)s1 - *(unsigned char*)s2;
}

void add_env_var(t_var_t **head, char *key, char *value)
{
	t_var_t *new_node;
	t_var_t *current;

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
	new_node = malloc(sizeof(t_var_t));
	new_node->key = ft_strdup(key);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->next = *head;
	*head = new_node;
}

void initialize_environment(t_var_t **head, char **env)
{
	char *key;
	char *value;
	int i;
	*head = NULL;
	i = 0;
    // printf("fsdfsd\n");
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

void free_env(t_var_t *head)
{
	t_var_t *current;
	t_var_t *temp;

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

void print_env(t_var_t *head, int bool)
{
	t_var_t *current = head;

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

char* env_nav(t_var_t **head,char * key){

	t_var_t *current;
	current = *head;
	char *outsider;
	while (current != NULL)
	{
		if(ft_strcmp(current->key,key)== 0)
		{
			outsider = ft_strdup(current->value);
		}
		current = current->next;
	}
	return outsider;


}