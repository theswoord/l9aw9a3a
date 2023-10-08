/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 06:31:24 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 06:31:25 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_shell *mstruct, int ac, char **av)
{
	print_env(mstruct->envlist, 0);
	error_set(mstruct, SUCCESS, 0);
}
