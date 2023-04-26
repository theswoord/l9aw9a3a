/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:11 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:00:48 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	b;
	size_t	d;

	b = 0;
	d = ft_strlen(src);
	if (dstsize == 0)
	{
		return (d);
	}
	while (b < dstsize - 1 && src[b])
	{
		dst[b] = src[b];
		b++;
	}
	dst[b] = '\0';
	return (d);
}
