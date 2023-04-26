/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:16 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 01:14:45 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*stri;

	i = 0;
	if (!s)
		return (0);
	stri = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!stri)
		return (0);
	while (s[i])
	{
		stri[i] = f(i, s[i]);
		i++;
	}
	stri[i] = '\0';
	return (stri);
}
