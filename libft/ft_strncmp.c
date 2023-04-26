/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:18 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:01:00 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			b;
	int				c;
	unsigned char	*compare1;
	unsigned char	*compare2;

	b = 0;
	c = 0;
	compare1 = (unsigned char *)s1;
	compare2 = (unsigned char *)s2;
	while ((compare2[b] || compare1[b]) && (b < n))
	{
		if (compare1[b] != compare2[b])
		{
			c = (compare1[b] - compare2[b]);
			return (c);
		}
		b++;
	}
	return (0);
}
