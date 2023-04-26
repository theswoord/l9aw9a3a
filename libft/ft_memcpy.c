/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:32 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:23:05 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	a;
	char	*min;
	char	*ila;

	a = 0;
	ila = (char *)dst;
	min = (char *)src;
	if (ila == 0 && min == 0)
		return (0);
	while (a < n)
	{
		ila[a] = min[a];
		a++;
	}
	return (dst);
}
