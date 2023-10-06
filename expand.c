/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:42 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:32:43 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	qidentify(t_shell *g_struct, t_tlist *token)
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
					tmp->str = expander_qv2(g_struct, tmp->str);
			}
			tmp->str = quotes_moncef(tmp->str);
		}
		tmp = tmp->next;
	}
}

void	expander_init(t_shell *g_struct, t_tlist *head, t_var_t *env)
{
	t_tlist	*tmp;
	int		i;

	tmp = head;
	i = 0;
	while (tmp != NULL)
	{
		if (tmp->value == EXPAND)
		{
			tmp->str = expanded(g_struct, tmp->str);
		}
		tmp = tmp->next;
	}
}

char	*expanded(t_shell *g_struct, char *str)
{
	t_var_t	*tmp;
	char	*first;
	char	*later;
	char	*expantion;
	int		checked;

	tmp = g_struct->envlist;
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

char	*expanded_q(t_shell *g_struct, char *str)
{
	t_var_t	*tmp;
	char	*first;
	char	*later;
	char	*expantion;
	int		checked;
	char	*rest;
	char	*final;

	tmp = g_struct->envlist;
	checked = 0;
	first = ft_substr(str, 0, pos(str, '$'));
	later = ft_strchr(str, '$') + 1;
	rest = ft_strrchr(str, '"');
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->key, later, pos(later, ' ')) == 0)
		{
			expantion = ft_strdup(tmp->value);
			final = recombinator(first, expantion, rest);
			free(str);
			return (final);
		}
		checked++;
		if (checked == g_struct->count)
		{
			expantion = ft_strdup("");
			final = recombinator(first, expantion, rest);
		}
		tmp = tmp->next;
	}
	free(str);
	return (final);
}

char	*env_expander(t_shell *g_struct, t_var_t *head, char *key)
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
