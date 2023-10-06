/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexic_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:11 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:52:26 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	e_search(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

int	twodlen(char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i])
		i++;
	return (i);
}

void	str_replacement(char *str)
{
	int	i;
	int	o;
	int	c;

	i = 0;
	o = 0;
	c = 1;
	while (str[i] != '\0')
	{
		if ((str[i] == '"' || str[i] == '\'') && c == 1)
		{
			o = 1;
			c = 0;
			i++;
		}
		if ((str[i] == '"' || str[i] == '\'') && o == 1)
		{
			c = 1;
			o = 0;
			i++;
		}
		if (o == 1 && c == 1)
		{
			o = 0;
			c = 0;
		}
		if (str[i] == ' ' && o == 0)
			str[i] = '\n';
		i++;
	}
}
