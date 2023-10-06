/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:41:07 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:41:08 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quotes_errors(char *str)
{
	int		i;
	bool	s_q;
	bool	d_q;

	i = 0;
	s_q = true;
	d_q = true;
	while (str[i])
	{
		if (str[i] == '\"' && s_q == true)
		{
			d_q = !d_q;
		}
		else if (str[i] == '\'' && d_q == true)
		{
			s_q = !s_q;
		}
		i++;
	}
	return (s_q && d_q);
}

bool	list_check(t_tlist *head)
{
	t_tlist	*current;

	current = head;
	while (current != NULL)
	{
		if (quotes_errors(current->str) == false)
			return (false);
		if (current->value == PIPE && current->queue == 0)
			return (false);
		if ((current->value == APPEND || current->value == REDIR
				|| current->value == REDIW || current->value == DOC
				|| current->value == PIPE) && !current->next)
		{
			return (false);
		}
		if ((current->value == REDIR || current->value == REDIW
				|| current->value == PIPE) && (current->next->value != WORD
				&& current->next->value != OPT && current->next->value != QUOTES
				&& current->next->value != EXPAND))
		{
			return (false);
		}
		if ((current->value == APPEND || current->value == REDIR
				|| current->value == REDIW || current->value == DOC)
			&& current->next == NULL)
		{
			return (false);
		}
		current = current->next;
	}
	return (true);
}

char	*delete_pos(char *str, int pos)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	result = malloc(ft_strlen(str));
	while (str[i])
	{
		if (j == pos)
		{
			i++;
		}
		result[j] = str[i];
		j++;
		i++;
	}
	result[j] = '\0';
	free(str);
	return (result);
}

// 7di m3a had file checked ++ o >> |       << |
char	*extract_from_in_list(t_shell *g_struct, t_var_t *tlist, char *key)
{
	t_var_t	*current;
	int		checked;

	current = tlist;
	checked = 0;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			return (current->value);
		}
		checked++;
		if (checked == g_struct->count)
			return ("");
		current = current->next;
	}
	return ("");
}

char	*strdelch(char *str, char ch)
{
	char	*current;
	char	*tail;

	current = str;
	tail = str;
	while (*tail)
	{
		if (*tail == ch)
		{
			tail++;
		}
		else
		{
			*current++ = *tail++;
		}
	}
	*current = 0;
	return (str);
}
