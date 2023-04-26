/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 17:51:18 by nbouhali          #+#    #+#             */
/*   Updated: 2022/10/26 01:59:16 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	sayze(int n)
{
	int	a;

	a = 0;
	if (n <= 0)
	{
		a++;
	}
	while (n != 0)
	{
		n = n / 10;
		a++;
	}
	return (a);
}

static void	affecting(char *stri, long shlong, int kharij, int lkher)
{
	while (shlong != 0)
	{
		kharij = shlong - (shlong / 10) * 10;
		stri[lkher] = kharij + '0';
		shlong = shlong / 10;
		lkher--;
	}
}

char	*ft_itoa(int n)
{
	long	shlong;
	int		lkher;
	int		lafindelafin;
	char	*stri;
	int		kharij;

	shlong = n;
	lkher = sayze(n) - 1;
	lafindelafin = sayze(n);
	kharij = 0;
	stri = malloc(sayze(n) * sizeof(char) + 1);
	if (!stri)
		return (0);
	if (shlong < 0)
	{
		shlong *= -1;
		stri[0] = '-';
	}
	if (shlong == 0)
		stri[0] = '0';
	affecting(stri, shlong, kharij, lkher);
	stri[lafindelafin] = '\0';
	return (stri);
}
