/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 23:44:03 by nbouhali          #+#    #+#             */
/*   Updated: 2022/11/18 03:28:58 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	strlenght(char *base)
{
	int	a;

	a = 0;
	while (base[a])
	{
		a++;
	}
	return (a);
}

int	blastelse(unsigned int thef, char *base, int count)
{
	if (thef < (10 + 6 * (strlenght(base) == 16)))
	{
		write(1, &base[thef], 1);
		count++;
	}
	else
	{
		count = blastelse(thef / (10 + 6 * (strlenght(base) == 16)), base,
				count);
		count = blastelse(thef - (thef / (10 + 6 * (strlenght(base) == 16)))
				* (10 + 6 * (strlenght(base) == 16)), base, count);
	}
	return (count);
}

int	ft_putnbr(int nbr, char *base)
{
	int				count;
	unsigned int	thef;

	count = 0;
	if (strlenght(base) == 16)
		thef = nbr;
	else
	{
		if (nbr < 0)
			write(1, "-", 1);
		thef = (1 - 2 * (nbr < 0)) * nbr;
	}
	count += blastelse(thef, base, count);
	count += (nbr < 0 && strlenght(base) != 16);
	return (count);
}

// 15: lenght
// 27: methode i used to halven 
// 27 bis:the size ot the main function 
// 29: if the number is < to the base i write it 
// 36: if not < base i need to / and % it until it's smoller
// 50: if the base is hexa && to get 
// 50:the -input hexa , i cast it to an unsigned in order to get the max value
// 52 - 57: if number (base 10) is negative type the "-" , 
// 56: if it's positive stay positive else become positive |x|
// 59: adds to the count of the "-" i didn't add f line 
// 55: 7it ila tzad 9bl blastelse kaytchetet count for good hhh