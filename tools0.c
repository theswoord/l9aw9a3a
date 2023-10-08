/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:39:01 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:39:02 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_pointers2(t_redi_node *head)
{
	t_redi_node	*current;

	current = head;
	while (current != NULL)
	{
		printf("ptr |%p| strptr |%p| \n", current, current->file);
		current = current->next;
	}
}

void	print_pointers(t_tlist *head)
{
	t_tlist	*current;

	current = head;
	while (current != NULL)
	{
		printf("ptr |%p| str |%s| strptr |%p| \n", current, current->str,
			current->str);
		current = current->next;
	}
}

void	special_free(t_shell *g_struct)
{
	t_tlist	*current;

	current = g_struct->tlist;
	while (current != NULL)
	{
		if (current->str)
		{
			free(current->str);
		}
		if (current->next)
		{
			free(current->next->str);
			free(current->next);
		}
		free(current);
		current = NULL;
	}
}

int	list_size(t_tlist *head)
{
	t_tlist	*current;
	int		size;

	current = head;
	size = 0;
	while (current != NULL)
	{
		size++;
		current = current->next;
	}
	return (size);
}

char	**from_list_to_arr(t_tlist *head)
{
	int		i;
	int		size;
	char	**arr;
	t_tlist	*current;

	i = 0;
	size = list_size(head);
	current = head;
	arr = malloc(size * sizeof(char *) + 1);
	while (current != NULL)
	{
		arr[i] = current->str;
		i++;
		current = current->next;
	}
	arr[i] = NULL;
	return (arr);
}
