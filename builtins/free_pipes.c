/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:22 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 05:58:38 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	free_redirections(t_redi_node **redirect_node)
{
	t_redi_node	*current_redi;
	t_redi_node	*temp;

	current_redi = *redirect_node;
	while (current_redi != NULL)
	{
		temp = current_redi;
		current_redi = current_redi->next;
		free(temp->file);
		free(temp);
		temp = NULL;
	}
}

void	free_pipes_node(t_node **command_node)
{
	int			i;
	t_node		*current;
	t_redi_node	*current_redi;
	t_redi_node	*temp;

	if (*command_node == NULL)
		return ;
	current = *command_node;
	if (current->args != NULL)
	{
		i = -1;
		while (current->args[++i] != NULL)
			free(current->args[i]);
		free(current->args);
	}
	free_redirections(&(current->redirect));
	free_pipes_node(&((*command_node)->next));
	free(*command_node);
	*command_node = NULL;
}
