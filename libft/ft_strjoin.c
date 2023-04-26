/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:05 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:00:33 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*tkhlita;
	int		a;
	int		d;

	if (s1 == 0 || s2 == 0)
	{
		return (0);
	}
	tkhlita = 0;
	a = 0;
	tkhlita = malloc((ft_strlen(s1) + ft_strlen(s2)) * sizeof(char) + 1);
	if (!tkhlita)
		return (0);
	while (a < (int)ft_strlen(s1))
	{
		tkhlita[a] = s1[a];
		a++;
	}
	d = 0;
	while (d < (int)ft_strlen(s2))
	{
		tkhlita[a++] = s2[d++];
	}
	tkhlita[a] = '\0';
	return (tkhlita);
}
