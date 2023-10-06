/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:39 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:32:40 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_exit_to_env(t_shell *g_struct, int exit)
{
	if (g_struct->exit_arr)
	{
		free(g_struct->exit_arr);
	}
	else
	{
		return (ft_itoa(g_struct->exit_status));
	}
	return (NULL);
}

void	update_exit(t_shell *g_struct)
{
	static int	i = 0;

	if (i != 0)
		free(g_struct->exit_arr);
	g_struct->exit_arr = ft_itoa(g_struct->exit_status);
	add_env_var(&g_struct->envlist, "?", g_struct->exit_arr);
	i++;
}

void	modify_env(t_shell *g_struct, t_tlist *token)
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
			if (add_env_var(&g_struct->envlist, key, value))
				g_struct->count++;
			free(key);
		}
		tmp = tmp->next;
	}
}
