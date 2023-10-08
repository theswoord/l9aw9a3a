/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:14 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 07:59:34 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	add_to_environ(char *argument, t_var_t **env)
{
	char	*key;
	char	*value;

	if (!argument || *argument == '\0')
		return ;
	if (ft_charfind(argument, '=') != 0)
	{
		key = ft_substr(argument, 0, ft_charfind(argument, '='));
		value = ft_strchr(argument, '=') + 1;
	}
	else
	{
		key = ft_strdup(argument);
		value = NULL;
	}
	add_env_var(env, key, value);
	free(key);
}

void	export(t_shell *mstruct, int ac, char **av, char **env)
{
	int	i;

	(void)env;
	i = 0;
	while (++i < ac)
		add_to_environ(av[i], &mstruct->envlist);
	if (ac == 1)
		print_env(mstruct->envlist, 1);
}
