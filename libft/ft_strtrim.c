/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:27 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 06:32:07 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	bidaya(const char *phrase, const char *set)
{
	int		found;
	int		start;
	int		finish;
	size_t	j;

	start = 0;
	finish = ft_strlen(phrase) - 1;
	while (start < finish)
	{
		found = 0;
		j = 0;
		while (j < ft_strlen(set))
		{
			if (phrase[start] == set[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (found == 0)
			break ;
		start++;
	}
	return (start);
}

static size_t	nihaya(const char *phrase, const char *set)
{
	int		found;
	int		finish;
	size_t	j;

	finish = ft_strlen(phrase) - 1;
	while (0 < finish)
	{
		found = 0;
		j = 0;
		while (j < ft_strlen(set))
		{
			if (phrase[finish] == set[j])
			{
				found = 1;
				break ;
			}
			j++;
		}
		if (found == 0)
			break ;
		finish--;
	}
	return (finish);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lowel;
	int		lekher;
	int		b;
	char	*natija;

	if (!set || !s1)
		return (0);
	b = 0;
	lowel = bidaya(s1, set);
	lekher = nihaya(s1, set);
	if (lekher < lowel)
		return ((char *)ft_calloc(sizeof(char), 1));
	natija = malloc((lekher - lowel) * sizeof(char) + 2);
	if (!natija)
		return (0);
	while (lowel <= lekher)
	{
		natija[b++] = s1[lowel++];
	}
	natija[b] = '\0';
	return (natija);
}
