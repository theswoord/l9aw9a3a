/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:44:10 by nbouhali          #+#    #+#             */
/*   Updated: 2023/10/08 04:45:50 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	pwd_command(t_shell *g_shell)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		printf("%s\n", cwd);
	else
	{
		g_shell->error_name = PERMISSION_DENIED_FILE;
		exit_status_error(g_shell, 1);
		print_error_message(g_shell);
		return ;
	}
	g_shell->error_name = SUCCESS;
	exit_status_error(g_shell, 1);
	return ;
}
