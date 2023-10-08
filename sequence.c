/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sequence.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:34:59 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 07:24:18 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tlist	*pipes_copy(t_tlist *current)
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

void	pipes_list_init(t_tlist **current, t_node **node,
		t_shell *mstruct)
{
	(*current) = mstruct->tlist;
	(*node) = (t_node *)ft_calloc(1, sizeof(t_node));
	(*node)->next = NULL;
}

void	pipes_list_check(t_node *node, t_node *last, t_shell *mstruct)
{
	if (!mstruct->pipes_list)
		mstruct->pipes_list = node;
	else
	{
		last = mstruct->pipes_list;
		while (last->next != NULL)
			last = last->next;
		last->next = node;
	}
}

void	pipes_list(t_shell *mstruct, int count, int i)
{
	t_tlist	*current;
	t_node	*node;
	t_node	*last;

	last = NULL;
	pipes_list_init(&current, &node, mstruct);
	node->args = ft_calloc((count + 1), sizeof(char *));
	while (i < count)
	{
		node->args[i++] = current->str;
		free(current);
		current = current->next;
	}
	node->redirect = NULL;
	pipes_list_check(node, last, mstruct);
	if (current == NULL)
		return ;
	free(current->str);
	free(current);
	mstruct->tlist = current->next;
}

void	redi_set(t_shell *mstruct)
{
	t_tlist	*current;

	current = mstruct->tlist;
	while (current != NULL)
	{
		if (current->is_file == true)
		{
			add_redi(&mstruct->redi_list, new_redi(current->str,
					current->value));
			current = current->next;
		}
		else
			current = current->next;
	}
}
