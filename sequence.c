/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:34:59 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 05:05:14 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	files_finder(t_tlist *head)
{
	t_tlist	*current;

	while (current != NULL && current->next)
	{
		if (current->value == REDIR || current->value == APPEND
			|| current->value == REDIW)
		{
			current->next->value = current->value;
			current->next->is_file = true;
		}
		if (ft_strcmp(current->str, ">") == 0 || ft_strcmp(current->str,
				">>") == 0 || ft_strcmp(current->str, "<") == 0)
			current->is_file = false;
		current = current->next;
	}
}

int	nodes_count(t_tlist **current)
{
	int	nodes;

	nodes = 0;
	while (*current != NULL)
	{
		if ((*current)->value == PIPE || (*current)->value == REDIR
			|| (*current)->value == REDIW || (*current)->value == APPEND)
		{
			(*current) = (*current)->next;
			return (nodes);
		}
		nodes++;
		(*current) = (*current)->next;
	}
	return (nodes);
}

t_tlist	*pipes_copy(t_tlist *head, t_tlist *current)
{
	while (current != NULL)
	{
		if (current->value == PIPE)
		{
			current = current->next;
			printf("%s\n", current->str);
			return (current);
		}
		current = current->next;
	}
	return (current);
}

void	pipes_list(t_shell *g_struct, int count)
{
	int		i;
	int		j;
	t_tlist	*current;
	t_node	*node;
	t_node	*last;

	i = 0;
	j = count;
	current = g_struct->tlist;
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	node->next = NULL;
	node->args = ft_calloc((count + 1), sizeof(char *));
	while (i < count)
	{
		node->args[i] = current->str;
		free(current);
		i++;
		current = current->next;
	}
	node->redirect = NULL;
	if (!g_struct->pipes_list)
		g_struct->pipes_list = node;
	else
	{
		last = g_struct->pipes_list;
		while (last->next != NULL)
			last = last->next;
		last->next = node;
	}
	if (current == NULL)
		return ;
	free(current->str);
	free(current);
	g_struct->tlist = current->next;
}

void	redi_set(t_shell *g_struct)
{
	t_tlist	*current;

	current = g_struct->tlist;
	while (current != NULL)
	{
		if (current->is_file == true)
		{
			add_redi(&g_struct->redi_list, new_redi(current->str,
					current->value));
			current = current->next;
		}
		else
			current = current->next;
	}
}
