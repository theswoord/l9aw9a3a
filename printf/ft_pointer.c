/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:43:52 by nbouhali          #+#    #+#             */
/*   Updated: 2022/11/17 02:48:30 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	salahlong(unsigned long nbr, char *base)
{
	int	count;

	count = 0;
	if (nbr < 16)
	{
		write(1, &base[nbr], 1);
		count++;
	}
	else
	{
		count += salahlong(nbr / 16, base);
		count += salahlong(nbr - (nbr / 16) * 16, base);
	}
	return (count);
}
