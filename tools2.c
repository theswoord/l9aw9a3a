/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:41:46 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:41:47 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recombinator(char *first, char *later, char *rest)
{
	char	*result;

	result = ft_strjoingnl(first, later);
	result = ft_strjoingnl(result, rest);
	free(later);
	return (result);
}

char	*ft_strchrtill(const char *s, int c, int len)
{
	size_t	a;
	char	*mbdla;

	a = 0;
	mbdla = (char *)s;
	while (a <= ft_strlen(mbdla))
	{
		if (mbdla[a] == (char)c)
		{
			return (mbdla + a - len);
		}
		a++;
	}
	return (0);
}

char	*ft_strjoinmini(char *s1, char *s2)
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
	free(s2);
	return (tkhlita);
}

char	*ft_realloc(char *str, int size)
{
	char	*tmp;
	int		old_size;

	if (str == NULL)
	{
		return (ft_calloc(size, 1));
	}
	else if (size == 0)
	{
		free(str);
		return (NULL);
	}
	else
	{
		old_size = ft_strlen(str) + 1;
		tmp = ft_calloc(size, 1);
		ft_strlcpy(tmp, str, old_size);
		free(str);
		return (tmp);
	}
}

int	element_counter(t_tlist *head, int what)
{
	int		count;
	t_tlist	*current;

	count = 0;
	current = head;
	while (current != NULL)
	{
		if (current->value == what)
		{
			count++;
		}
		current = current->next;
	}
	return (count);
}
