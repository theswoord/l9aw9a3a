/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:42 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 06:09:24 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qidentify(t_shell *mstruct, t_tlist *token)
{
	t_tlist	*tmp;

	tmp = token;
	while (tmp != NULL)
	{
		if (tmp->value == QUOTES)
		{
			if (pos(tmp->str, '\"') != -1)
			{
				if (pos(tmp->str, '$') != -1)
					tmp->str = expander_qv2(mstruct, tmp->str);
			}
			tmp->str = quotes_remover(tmp->str);
		}
		tmp = tmp->next;
	}
}

void	expander_init(t_shell *mstruct, t_tlist *head, t_var_t *env)
{
	t_tlist	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value == EXPAND)
		{
			tmp->str = expanded(mstruct, tmp->str);
		}
		tmp = tmp->next;
	}
}

char	*expanded(t_shell *mstruct, char *str)
{
	t_var_t	*tmp;
	char	*first;
	char	*later;
	char	*expantion;
	int		checked;

	tmp = mstruct->envlist;
	checked = 0;
	first = ft_substr(str, 0, pos(str, '$'));
	later = ft_strchr(str, '$') + 1;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, later) == 0)
		{
			expantion = ft_strdup(tmp->value);
			free(str);
			str = ft_strjoingnl(first, expantion);
			return (free(expantion), str);
		}
		tmp = tmp->next;
	}
	free(str);
	return (ft_strjoingnl(first, ""));
}

char	*env_expander(t_shell *mstruct, t_var_t *head, char *key)
{
	t_var_t	*current;
	int		checked;

	current = head;
	checked = 0;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(key);
			return (ft_strdup(current->value));
		}
		current = current->next;
	}
	return (free(key), ft_strdup(""));
}
