/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:08 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:08:48 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	b;
	size_t	c;
	size_t	d;
	size_t	len;

	if (size == 0 && dst == 0)
		return (ft_strlen(src));
	c = ft_strlen(dst);
	d = ft_strlen(src);
	b = 0;
	if (size <= c || size == 0)
		return (d + size);
	len = size - c - 1;
	while (b < len && src[b])
	{
		dst[c + b] = src[b];
		b++;
	}
	dst[c + b] = '\0';
	return (d + c);
}
