/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 06:31:24 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 06:58:56 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_shell *mstruct, int ac, char **av)
{
	(void)ac;
	(void)av;
	print_env(mstruct->envlist, 0);
	error_set(mstruct, SUCCESS, 0);
}
