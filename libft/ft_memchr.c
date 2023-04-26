/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:27 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 01:59:26 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	b;
	char	*mbdla;

	b = 0;
	mbdla = (char *)s;
	while (b < n)
	{
		if (mbdla[b] == (char)c)
		{
			return (mbdla + b);
		}
		b++;
	}
	return (0);
}
