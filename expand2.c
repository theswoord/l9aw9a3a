/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:44 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 05:02:15 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*quotes_remover(char *str)
{
	int		i;
	int		j;
	bool	s_q;
	bool	d_q;
	char	*result;

	i = 0;
	j = 0;
	s_q = true;
	d_q = true;
	result = ft_calloc(ft_strlen(str), 1);
	while (str[i])
	{
		if (str[i] == '\"' && s_q == true)
		{
			d_q = !d_q;
			while (str[i] == '\"')
				i++;
		}
		else if (str[i] == '\'' && d_q == true)
		{
			s_q = !s_q;
			while (str[i] == '\'')
				i++;
		}
		result[j++] = str[i++];
	}
	free(str);
	return (result);
}

char	*expander_qv2(t_shell *g_struct, char *str)
{
	int		i;
	int		j;
	int		k;
	char	*request;
	char	*expantion;
	char	*out;

	i = 0;
	j = 0;
	k = 0;
	request = NULL;
	expantion = NULL;
	out = ft_calloc(ft_strlen(str) + 1, 1);
	while (str[i])
	{
		if (str[i] == '$')
		{
			i++;
			j = i;
			while (ft_isalnum(str[i]) == 1 || str[i] == '?')
				i++;
			request = ft_substr(str, j, i - j);
			expantion = env_expander(g_struct, g_struct->envlist, request);
			out = ft_strjoingnl(out, expantion);
			out = ft_realloc(out, (ft_strlen(str) + ft_strlen(expantion)));
			k += ft_strlen(expantion);
			free(expantion);
		}
		else
		{
			out[k] = str[i];
			out[k + 1] = '\0';
			k++;
			i++;
		}
	}
	free(str);
	return (out);
}

void	builtins(t_shell *g_struct, char **env, char **single_comm)
{
	if (ft_strcmp(single_comm[0], "cd") == 0)
	{
		cd_command(single_comm[1], env, g_struct);
		update_exit(g_struct);
	}
	else if (ft_strcmp(single_comm[0], "env") == 0)
	{
		ft_env(g_struct, twodlen(single_comm), single_comm);
		update_exit(g_struct);
	}
	else if (ft_strcmp(single_comm[0], "export") == 0)
	{
		if (twodlen(single_comm) == 1)
			print_env(g_struct->envlist, 1);
		export(g_struct, twodlen(single_comm), single_comm, env);
		update_exit(g_struct);
	}
	else if (ft_strcmp(single_comm[0], "unset") == 0)
	{
		ft_unset(twodlen(single_comm), single_comm, g_struct);
		update_exit(g_struct);
	}
	else if (ft_strcmp(single_comm[0], "exit") == 0)
	{
		ft_exit(single_comm, g_struct);
		update_exit(g_struct);
	}
	else if (ft_strcmp(single_comm[0], "pwd") == 0)
	{
		pwd_command(g_struct);
		update_exit(g_struct);
	}
	else if (ft_strcmp(single_comm[0], "echo") == 0)
	{
		echo_command(twodlen(single_comm), single_comm, g_struct);
		update_exit(g_struct);
	}
}

int	allspaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}
