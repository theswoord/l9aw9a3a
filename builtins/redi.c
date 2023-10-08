/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:34 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 06:09:24 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	redirections(t_redi_node *redirect_node, t_shell *mstruct)
{
	t_redi_node	*current;
	t_heredoc	*temp;

	current = redirect_node;
	while (current)
	{
		if (current->type == OUT)
			file_out(current->file);
		else if (current->type == APPEAND)
			file_append(current->file);
		else if (current->type == IN)
			file_in(current->file);
		else if (current->type == HEREDOC)
		{
			dup2(mstruct->heredoc_list->fd, 0);
			temp = mstruct->heredoc_list;
			mstruct->heredoc_list = mstruct->heredoc_list->next;
			free(temp);
		}
		else
			return ;
		current = current->next;
	}
}

t_redi_node	*new_redi(char *file, int type)
{
	t_redi_node	*new;

	new = malloc(sizeof(t_redi_node));
	new->file = file;
	new->type = type;
	new->next = NULL;
	return (new);
}

void	add_redi(t_redi_node **node, t_redi_node *new)
{
	t_redi_node	*head;

	if (!*node)
	{
		*node = new;
		return ;
	}
	head = *node;
	while (head->next)
		head = head->next;
	head->next = new;
}
