/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 04:11:30 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/10/08 06:09:24 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	close_pipes(int *pipes)
{
	close(pipes[0]);
	close(pipes[1]);
}

void	pipes_exec(t_node *current_node, t_shell *mstruct, int *pipes,
		int temp_fd)
{
	int		status;
	pid_t	pid;

	pipe(pipes);
	pid = fork();
	if (pid == 0)
	{
		if (temp_fd != -1)
		{
			dup2(temp_fd, STDIN_FILENO);
			close(temp_fd);
		}
		if (current_node->next != NULL)
			dup2(pipes[1], STDOUT_FILENO);
		close_pipes(pipes);
		redirections(current_node->redirect, mstruct);
		general_execution(mstruct, current_node->args, 0);
		exit(mstruct->exit_status);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			mstruct->exit_status = WEXITSTATUS(status);
	}
}

void	execute_pipelines(t_node **command_node, t_shell *mstruct)
{
	int		status;
	int		temp_fd;
	int		pipes[2];
	t_node	*current_node;

	if (*command_node == NULL)
		return ;
	current_node = *command_node;
	temp_fd = -1;
	while (current_node)
	{
		pipes_exec(current_node, mstruct, pipes, temp_fd);
		if (temp_fd != -1)
			close(temp_fd);
		temp_fd = pipes[0];
		close(pipes[1]);
		current_node = current_node->next;
	}
	close(temp_fd);
	while (wait(NULL) > 0)
	{
		continue ;
	}
	free_pipes_node(command_node);
	return ;
}

t_node	*new_node(char **arr, t_redi_node *redirect)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->args = arr;
	new->redirect = redirect;
	new->next = NULL;
	return (new);
}

void	add_node(t_node **node, t_node *new)
{
	t_node	*head;

	if (!*node)
	{
		*node = new;
		return ;
	}
	head = *node;
	while (head->next)
		head = head->next;
	head->next = new;
}
