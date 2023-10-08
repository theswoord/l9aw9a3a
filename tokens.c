/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:38:11 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:38:12 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ignore_spaces(char *s)
{
	int		i;
	int		opmax;
	int		counter;
	char	quotation_type;

	i = 0;
	quotation_type = s[i];
	opmax = 2;
	counter = 0;
	while (s[i] == quotation_type && s[i] != '\0' && counter++ < opmax)
		i++;
	return (i);
}

static int	ft_lenght(char *s)
{
	char	quotation_type;
	int		i;

	i = 0;
	if (s[i] == '>' || s[i] == '<' || s[i] == '|')
		i += ignore_spaces(s);
	else
	{
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0' && s[i] != '>'
			&& s[i] != '<' && s[i] != '|')
		{
			if (s[i] == '\"' || s[i] == '\'')
			{
				quotation_type = s[i++];
				while (s[i] != quotation_type && s[i] != '\0')
					i++;
			}
			i++;
		}
	}
	return (i);
}

static int	ft_count(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (s[i] != '\0')
			count++;
		i += ft_lenght(&s[i]);
	}
	return (count);
}

char	**ft_u_split(char *s)
{
	char	**splitted;
	int		splitted_iterator;
	int		i;
	int		lenght;

	splitted = (char **)ft_calloc((ft_count(s) + 1), sizeof(char *));
	i = 0;
	splitted_iterator = 0;
	while (s[i] != '\0')
	{
		while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
			i++;
		if (s[i] == '\0')
			break ;
		lenght = ft_lenght(&s[i]);
		splitted[splitted_iterator] = (char *)malloc(lenght + 1);
		ft_strlcpy(splitted[splitted_iterator++], &s[i], lenght + 1);
		i += lenght;
	}
	return (splitted);
}
