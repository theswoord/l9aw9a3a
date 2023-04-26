/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:58 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:00:22 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		b;
	char	*chi7aja;

	b = 0;
	b = ft_strlen(s1);
	chi7aja = malloc(b * sizeof(char) + 1);
	if (!chi7aja)
	{
		return (0);
	}
	ft_memcpy(chi7aja, s1, b);
	chi7aja[b] = '\0';
	return (chi7aja);
}
