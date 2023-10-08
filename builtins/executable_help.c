/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable_help.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:09 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 06:33:46 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*malloc_path(char *executable_path, char *dir_start, char *dir_end,
		int command_len)
{
	int	path_len;

	path_len = (dir_end - dir_start) + 1 + command_len + 1;
	executable_path = malloc(path_len);
	if (!executable_path)
	{
		printf("path allocation failed!\n");
		exit(1);
	}
	return (executable_path);
}

void	copy_path(char **executable_path, char *dir_start, char *dir_end,
		char *command)
{
	int	command_len;

	command_len = ft_strlen(command);
	ft_memcpy(*executable_path, dir_start, dir_end - dir_start);
	(*executable_path)[dir_end - dir_start] = '/';
	ft_memcpy(*executable_path + (dir_end - dir_start) + 1, command,
		command_len);
	(*executable_path)[(dir_end - dir_start) + 1 + command_len] = '\0';
}

void	execve_execute(char *executable_path, char **args, t_shell *g_shell)
{
	if (executable_path)
		if (access(executable_path, X_OK) == 0)
			execve(executable_path, args, g_shell->env);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
	{
		return (0);
	}
	i = 0;
	while (str[i])
		i++;
	return (i);
}
