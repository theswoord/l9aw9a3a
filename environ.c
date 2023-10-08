/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:39 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 07:28:10 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_exit_to_env(t_shell *mstruct)
{
	if (mstruct->exit_arr)
	{
		free(mstruct->exit_arr);
	}
	else
	{
		return (ft_itoa(mstruct->exit_status));
	}
	return (NULL);
}

void	update_exit(t_shell *mstruct)
{
	static int	i = 0;

	if (i != 0)
		free(mstruct->exit_arr);
	mstruct->exit_arr = ft_itoa(mstruct->exit_status);
	add_env_var(&mstruct->envlist, "?", mstruct->exit_arr);
	i++;
}

void	modify_env(t_shell *mstruct, t_tlist *token)
{
	t_tlist	*tmp;
	char	*key;
	char	*value;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->value == VAR)
		{
			key = ft_substr(tmp->str, 0, ft_charfind(tmp->str, '='));
			value = ft_strchr(tmp->str, '=') + 1;
			if (add_env_var(&mstruct->envlist, key, value))
				mstruct->count++;
			free(key);
		}
		tmp = tmp->next;
	}
}

void	files_finder(t_tlist *head)
{
	t_tlist	*current;

	current = head;
	while (current != NULL && current->next)
	{
		if (current->value == REDIR || current->value == APPEND
			|| current->value == REDIW || current->value == DOC)
		{
			current->next->value = current->value;
			current->next->is_file = true;
		}
		if (ft_strcmp(current->str, ">") == 0 || ft_strcmp(current->str,
				">>") == 0 || ft_strcmp(current->str, "<") == 0
			|| ft_strcmp(current->str, "<<") == 0)
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
			|| (*current)->value == REDIW || (*current)->value == APPEND
			|| (*current)->value == DOC)
		{
			(*current) = (*current)->next;
			return (nodes);
		}
		nodes++;
		(*current) = (*current)->next;
	}
	return (nodes);
}
