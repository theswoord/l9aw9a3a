/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:29 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:03:42 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			b;
	int				c;
	unsigned char	*jomla1;
	unsigned char	*jomla2;

	b = 0;
	c = 0;
	jomla1 = (unsigned char *)s1;
	jomla2 = (unsigned char *)s2;
	while (b < n)
	{
		if (jomla1[b] != jomla2[b])
		{
			c = jomla1[b] - jomla2[b];
			return (c);
		}
		b++;
	}
	return (0);
}
