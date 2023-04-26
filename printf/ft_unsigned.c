/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:44:15 by nbouhali          #+#    #+#             */
/*   Updated: 2022/11/17 19:28:40 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	caster(unsigned int nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr < (10))
	{
		write(1, &base[nbr], 1);
		count++;
	}
	else
	{
		count += ft_putnbr(nbr / (10), base);
		count += ft_putnbr(nbr - (nbr / 10) * (10), base);
	}
	return (count);
}
