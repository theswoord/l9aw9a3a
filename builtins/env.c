/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:44:48 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 04:47:34 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_shell *g_struct, int ac, char **av)
{
	print_env(g_struct->envlist, 0);
	g_struct->error_name = SUCCESS;
	exit_status_error(g_struct, 1);
}
