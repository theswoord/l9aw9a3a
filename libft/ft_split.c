/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:11:47 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:06:46 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	kalimat(char const *s, char c)

{
	int	i;
	int	ch7al;

	i = 0;
	ch7al = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
		{
			ch7al++;
		}
		i++;
	}
	return (ch7al);
}

char	**ft_split(char const *s, char c)

{
	int		i;
	int		fin;
	int		debut;
	char	**new;
	int		j;

	j = 0;
	i = -1;
	if (!s)
		return (0);
	new = (char **)malloc((kalimat(s, c) + 1) * sizeof(char *));
	if (!new)
		return (0);
	while (s[++i])
	{
		if (s[i] != c && (s[i - 1] == c || i == 0))
			debut = i;
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			fin = i;
			new[j++] = ft_substr(s, debut, fin - debut + 1);
		}
	}
	new[j] = NULL;
	return (new);
}
