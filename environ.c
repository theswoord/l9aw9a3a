/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:39 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 06:09:24 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_exit_to_env(t_shell *mstruct, int exit)
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
