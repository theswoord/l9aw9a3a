/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:44:07 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 04:46:00 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	output_out(int fd)
{
	dup2(fd, 1);
	close(fd);
}

void	output_in(int fd)
{
	dup2(fd, 0);
	close(fd);
}

void	file_out(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	output_out(fd);
}

void	file_append(char *file)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	output_out(fd);
}

void	file_in(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	output_in(fd);
}

void	redirections(t_redi_node *redirect_node, t_shell *g_struct)
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
			dup2(g_struct->heredoc_list->fd, 0);
			temp = g_struct->heredoc_list;
			g_struct->heredoc_list = g_struct->heredoc_list->next;
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
