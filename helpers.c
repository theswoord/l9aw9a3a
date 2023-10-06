/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:04 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:50:05 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_charfind(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (i);
		i++;
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

int	add_env_var(t_var_t **head, char *key, char *value)
{
	t_var_t	*new_node;
	t_var_t	*current;

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
			return (0);
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
	return (1);
}

void	initialize_environment(t_shell *g_struct, t_var_t **head, char **env)
{
	char	*key;
	char	*value;
	int		i;

	*head = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_charfind(env[i], '=') != 0)
		{
			key = ft_substr(env[i], 0, ft_charfind(env[i], '='));
			value = ft_strchr(env[i], '=') + 1;
			add_env_var(head, key, value);
			g_struct->count++;
			free(key);
		}
		i++;
	}
}
