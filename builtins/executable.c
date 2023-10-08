/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executable.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouhali < nbouhali@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:11 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 07:01:47 by nbouhali         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

char	*find_executable_command(char *command, char *path)
{
	int		command_len;
	char	*dir_start;
	char	*dir_end;
	char	*executable_path;

	command_len = 0;
	dir_start = path;
	dir_end = path;
	while (*dir_end)
	{
		while (*dir_end && *dir_end != ':')
			dir_end++;
		executable_path = malloc_path(executable_path, dir_start, dir_start,
				command_len);
		copy_path(&executable_path, dir_start, dir_end, command);
		if (access(executable_path, X_OK) == 0)
			return (executable_path);
		free(executable_path);
		if (*dir_end == ':')
		{
			dir_end++;
			dir_start = dir_end;
		}
	}
	return (NULL);
}

void	execute_commands(char *command, char **args,
		t_shell *g_shell)
{
	char	*path;
	char	*executable_path;
	int		pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
			executable_path = ft_strdup(command);
		else
		{
			path = extract_from_in_list(g_shell, g_shell->envlist, "PATH");
			executable_path = find_executable_command(command, path);
		}
		execve_execute(executable_path, args, g_shell);
		error_set(g_shell, COMMAND_NOT_FOUND, 1);
		exit(g_shell->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_shell->exit_status = WEXITSTATUS(status);
	}
}

// zedt strcute l kbir hna bach ypassi l error msg
void	execute_commands_pipes(char *command, char **args, char **env,
		t_shell *g_shell)
{
	char	*path;
	char	*executable_path;

	if ((command[0] == '.' && command[1] == '/') || command[0] == '/')
		executable_path = ft_strdup(command);
	else
	{
		path = extract_from_in_list(g_shell, g_shell->envlist, "PATH");
		executable_path = find_executable_command(command, path);
	}
	if (executable_path)
		if (access(executable_path, X_OK) == 0)
			execve(executable_path, args, env);
	error_set(g_shell, COMMAND_NOT_FOUND, 1);
	exit(g_shell->exit_status);
}

void	general_execution(t_shell *mstruct, char **args, int fork)
{
	if (ft_strcmp(args[0], "cd") == 0)
		cd_command(args[1], mstruct);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(mstruct, twodlen(args), args);
	else if (ft_strcmp(args[0], "export") == 0)
		export(mstruct, twodlen(args), args, mstruct->env);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(twodlen(args), args, mstruct);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, mstruct);
	else if (ft_strcmp(args[0], "pwd") == 0)
		pwd_command(mstruct);
	else if (ft_strcmp(args[0], "echo") == 0)
		echo_command(twodlen(args), args, mstruct);
	else if (fork == 1)
		execute_commands(args[0], args, mstruct);
	else
		execute_commands_pipes(args[0], args, mstruct->env, mstruct);
}
