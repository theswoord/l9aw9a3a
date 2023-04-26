/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:35 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 01:59:43 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*fin;
	char	*mnin;

	if (!dst && !src)
	{
		return (0);
	}
	fin = (char *)dst;
	mnin = (char *)src;
	if (fin > mnin)
	{
		while (len > 0)
		{
			fin[len - 1] = mnin[len - 1];
			len--;
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
