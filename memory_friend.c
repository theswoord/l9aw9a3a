/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_friend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 04:50:40 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/06 04:51:29 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tableau(char **tableau, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}

void	free_tableauv2(char **tableau)
{
	int	i;

	i = 0;
	while (tableau[i])
	{
		free(tableau[i]);
		i++;
	}
	free(tableau);
}
