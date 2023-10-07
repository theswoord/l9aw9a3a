/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:29 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/07 21:57:33 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(t_node *head)
{
	t_node	*current;
	t_node	*temp;

	current = head;
	while (current->next != NULL)
	{
		temp = current;
		current = current->next;
		free_tableauv2(temp->args);
		free(temp);
	}
	free(current);
}

void	free_tokens(t_tlist *head)
{
	t_tlist	*current;
	t_tlist	*temp;

	current = head;
	while (current != NULL)
	{
		temp = current;
		current = current->next;
		free(temp->str);
		free(temp);
	}
}

int	typefinder(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '$')
			return (EXPAND);
		else if (line[i] == '<' && line[i + 1] == '<')
			return (DOC);
		else if (line[i] == '>' && line[i + 1] == '>')
			return (APPEND);
		else if (line[i] == '<' && line[i + 1] != '<')
			return (REDIR);
		else if (line[i] == '-' && ft_isprint(line[i + 1]) == 1)
			return (OPT);
		else if (line[i] == '|')
			return (PIPE);
		else if (line[i] == '>')
			return (REDIW);
		else if (line[i] == '=' && line[i - 1])
			return (VAR);
		else if (line[i] == '\'' || line[i] == '\"')
			return (QUOTES);
	}
	return (WORD);
}

int	find_in_list(t_var_t *head, char *search)
{
	t_var_t	*current;

	current = head;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, search) == 0)
			return (1);
		current = current->next;
	}
	return (0);
}

void	print_tokens(t_tlist *head)
{
	t_tlist	*current;

	current = head;
	while (current != NULL)
	{
		printf("%s %d %d\n", current->str, current->value, current->queue);
		current = current->next;
	}
}
