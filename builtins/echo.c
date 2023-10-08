/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:01 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 05:44:11 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	check_n(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo_child(int size, char **args, t_shell *g_struct)
{
	int	i;
	int	skip_newline;

	skip_newline = check_n(args[1]);
	i = skip_newline + 1;
	while (args && args[i])
	{
		if (check_n(args[i]))
			i++;
		else
			break ;
	}
	while (i < size)
	{
		printf("%s", args[i]);
		if (i < size - 1)
			printf(" ");
		i++;
	}
	if (!skip_newline)
		printf("\n");
	g_struct->error_name = SUCCESS;
	exit_status_error(g_struct);
}

void	echo_command(int size, char **args, t_shell *g_struct)
{
	echo_child(size, args, g_struct);
}
