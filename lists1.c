/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:32 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 07:12:23 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_var_t *head)
{
	t_var_t	*current;
	t_var_t	*temp;

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

void	print_env(t_var_t *head, int boole)
{
	t_var_t	*current;

	current = head;
	while (current != NULL)
	{
		if (boole == 1)
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

char	*env_nav(t_var_t **head, char *key)
{
	t_var_t	*current;
	char	*outsider;

	current = *head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			outsider = ft_strdup(current->value);
		}
		current = current->next;
	}
	return (outsider);
}

void	token_list(t_tlist **head, char *tok, int type, int queue)
{
	t_tlist	*current;
	t_tlist	*new_node;

	current = *head;
	new_node = malloc(sizeof(t_tlist));
	new_node->str = ft_strdup(tok);
	if (type)
		new_node->value = type;
	new_node->queue = queue;
	new_node->is_file = false;
	new_node->next = NULL;
	if (*head == NULL)
		*head = new_node;
	else
	{
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	add_token_list(t_tlist **head, char **tab)
{
	int		i;

	i = 0;
	*head = NULL;
	while (tab[i] != NULL)
	{
		token_list(head, tab[i], typefinder(tab[i]), i);
		i++;
	}
}
