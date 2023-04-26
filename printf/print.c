/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali <nbouhali@student.1337.ma >       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:10:53 by nbouhali          #+#    #+#             */
/*   Updated: 2022/11/18 03:29:45 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

int	check(char i, va_list args)
{
	int	counter;

	counter = 0;
	if (i == 'c')
		counter += ft_putchar(va_arg(args, int));
	else if ((i == 'd' || i == 'i'))
		counter += ft_putnbr(va_arg(args, int), "0123456789");
	else if (i == 's')
		counter += ft_putstr(va_arg(args, char *));
	else if (i == 'x')
		counter += ft_putnbr(va_arg(args, int), "0123456789abcdef");
	else if (i == 'X')
		counter += ft_putnbr(va_arg(args, int), "0123456789ABCDEF");
	else if (i == 'u')
		counter += caster(va_arg(args, unsigned int), "0123456789");
	else if (i == '%')
		counter += ft_putchar('%');
	else if (i == 'p')
	{
		counter += ft_putstr("0x");
		counter += salahlong(va_arg(args, long), "0123456789abcdef");
	}
	return (counter);
}

int	ft_printf(const char *str, ...)

{
	int		count;
	int		a;
	va_list	args;

	va_start(args, str);
	a = 0;
	count = 0;
	while (str[a])
	{
		if (str[a] == '%')
		{
			count += check(str[a + 1], args);
			a += 2;
		}
		else
		{
			write(1, &str[a], 1);
			a += 1;
			count++;
		}
	}
	va_end(args);
	return (count);
}

//24	: d & i kaydkhl lihom int 3ady o kaytktbo b base 10;
//26	: s , katchd jomla char*
//28-30 : x , putnbr ghir had lmera b base 16 
//bis: o kaydkhlo int 7it aslan aytbdl l unsigned   
// 39 	: p , ikh 3la error X years
//bis: o ana mdarb m3ah kolha ilghi blghah long rajol !