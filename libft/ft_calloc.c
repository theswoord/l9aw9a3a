/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:02 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 01:58:43 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	int		kay7sb;
	int		a;
	char	*array;

	kay7sb = 0;
	a = count * size;
	array = malloc(size * count);
	if (!array)
	{
		return (0);
	}
	while (kay7sb < a)
	{
		array[kay7sb] = '\0';
		kay7sb++;
	}
	return (array);
}
