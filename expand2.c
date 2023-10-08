/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:32:44 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/07 22:52:33 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quotes_rmvr(t_lesindex *indes, char *str, bool s_q, bool d_q)
{
	while (str[indes->i])
	{
		if (str[indes->i] == '\"' && s_q == true)
		{
			d_q = !d_q;
			while (str[indes->i] == '\"')
				indes->i++;
		}
		else if (str[indes->i] == '\'' && d_q == true)
		{
			s_q = !s_q;
			while (str[indes->i] == '\'')
				indes->i++;
		}
		indes->result[indes->j++] = str[indes->i++];
	}
}

char	*quotes_remover(char *str)
{
	t_lesindex	indes;
	bool		s_q;
	bool		d_q;

	indes.i = 0;
	indes.j = 0;
	s_q = true;
	d_q = true;
	indes.result = ft_calloc(ft_strlen(str), 1);
	quotes_rmvr(&indes, str, s_q, d_q);
	free(str);
	return (indes.result);
}

void	expanderv2(t_shell *g_struct, t_lesindex *indes, char *expantion,
		char *str)
{
	while (str[indes->i])
	{
		if (str[indes->i] == '$')
		{
			indes->i++;
			indes->j = indes->i;
			while (ft_isalnum(str[indes->i]) == 1 || str[indes->i] == '?')
				indes->i++;
			expantion = env_expander(g_struct, g_struct->envlist, ft_substr(str,
						indes->j, indes->i - indes->j));
			indes->out = ft_strjoingnl(indes->out, expantion);
			indes->out = ft_realloc(indes->out, (ft_strlen(str)
						+ ft_strlen(expantion)));
			indes->k += ft_strlen(expantion);
			free(expantion);
		}
		else
		{
			indes->out[indes->k] = str[indes->i];
			indes->out[indes->k + 1] = '\0';
			indes->k++;
			indes->i++;
		}
	}
}

char	*expander_qv2(t_shell *g_struct, char *str)
{
	t_lesindex	indes;
	char		*expantion;
	char		*out;

	indes.i = 0;
	indes.j = 0;
	indes.k = 0;
	indes.out = ft_calloc(ft_strlen(str) + 1, 1);
	expanderv2(g_struct, &indes, expantion, str);
	free(str);
	return (indes.out);
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
