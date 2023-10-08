/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:32 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 05:35:43 by zbenaiss         ###   ########.fr       */
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
		error_set(g_shell, PERMISSION_DENIED_FILE, 1);
		return ;
	}
	g_shell->error_name = SUCCESS;
	exit_status_error(g_shell);
	return ;
}
