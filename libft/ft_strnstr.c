/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:52:22 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 02:09:04 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;
	char	*tben;
	char	*lbra;

	a = 0;
	tben = (char *)haystack;
	lbra = (char *)needle;
	if (!haystack && len == 0)
		return (0);
	if (needle[a] == '\0')
		return (tben);
	while (a < len && tben[a])
	{
		b = 0;
		while (tben[a + b] == lbra[b] && b < ft_strlen(needle))
		{
			b++;
			if (b == ft_strlen(needle) && a + b <= len)
				return (tben + a);
		}
		a++;
	}
	return (0);
}
