/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:55:22 by nbouhali          #+#    #+#             */
/*   Updated: 2023/01/13 19:48:35 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlengnl(char *s)
{
	size_t	a;

	a = 0;
	while (s[a] != '\0')
	{
		a++;
	}
	return (a);
}

ssize_t	pos(char *s, char c)
{
	size_t	a;

	a = 0;
	while (a <= ft_strlengnl(s))
	{
		if (s[a] == c)
		{
			return (a);
		}
		a++;
	}
	return (-1);
}

char	*ft_strjoingnl(char *s1, char *s2)
{
	char	*tkhlita;
	int		a;
	int		d;
	int		ls1;
	int		ls2;

	ls1 = ft_strlengnl(s1);
	ls2 = ft_strlengnl(s2);
	a = 0;
	tkhlita = (char *)ft_calloc((ls1 + ls2) + 1, 1);
	if (!tkhlita)
		return (0);
	while (a < ls1)
	{
		tkhlita[a] = s1[a];
		a++;
	}
	d = 0;
	while (d < ls2)
	{
		tkhlita[a++] = s2[d++];
	}
	free(s1);
	return (tkhlita);
}

char	*ft_substrgnl(char *s, unsigned int start, size_t len)
{
	size_t			b;
	char			*subs;
	unsigned int	test;

	if (!s)
	{
		return (0);
	}
	if (len > ft_strlengnl(s))
		len = ft_strlengnl(s);
	b = 0;
	test = ft_strlengnl(s);
	subs = malloc(len * sizeof(char) + 1);
	if (!subs)
		return (0);
	while (b < len && test >= start)
	{
		subs[b] = s[start];
		b++;
		start++;
	}
	subs[b] = '\0';
	return (subs);
}

void	ft_bzerognl(void *s, size_t n)
{
	size_t	a;
	char	*str;

	a = 0;
	str = (char *)s;
	while (a < n)
	{
		str[a++] = '\0';
	}
}
