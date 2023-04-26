/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:25 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:01:09 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*mbdla;
	int		b;

	mbdla = (char *)s;
	b = ft_strlen(s);
	while (b >= 0)
	{
		if (mbdla[b] != (char)c)
		{
			b--;
		}
		if (mbdla[b] == (char)c)
		{
			return (mbdla + b);
		}
		b--;
	}
	return (0);
}
