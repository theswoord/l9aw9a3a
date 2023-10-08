/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:04 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 04:11:05 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_shell *g_struct, int ac, char **av)
{
	print_env(g_struct->envlist, 0);
	error_set(g_struct, SUCCESS, 0);
}
