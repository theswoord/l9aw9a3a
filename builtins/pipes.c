#include "builtins.h"

void free_redirections(t_redi_node **redirect_node)
{
	t_redi_node *current_redi;
	t_redi_node *temp;

	current_redi = *redirect_node;
	while (current_redi != NULL)
	{
		temp = current_redi;
		current_redi = current_redi->next;
		free(temp->file);
		free(temp);
		temp = NULL;
	}
}

void free_pipes_node(t_node **command_node)
{
	int i;
	t_node *current;
	t_redi_node *current_redi;
	t_redi_node *temp;

	if (*command_node == NULL)
		return;
	current = *command_node;
	if (current->args != NULL)
	{
		i = -1;
		while (current->args[++i] != NULL)
			free(current->args[i]);
		free(current->args);
	}
	free_redirections(&(current->redirect));
	free_pipes_node(&((*command_node)->next));

	free(*command_node);
	*command_node = NULL;
}

void pipes_exec(t_node *current_node, t_shell *g_struct, int *pipes, int temp_fd)
{
	int status;

	pipe(pipes);
		pid_t pid = fork();
		if (pid == 0)
		{
			if (temp_fd != -1)
			{
				dup2(temp_fd, STDIN_FILENO);
				close(temp_fd);
			}
			if (current_node->next != NULL)
				dup2(pipes[1], STDOUT_FILENO);
			close(pipes[0]);
			close(pipes[1]);
			redirections(current_node->redirect, g_struct);
			general_execution(g_struct, current_node->args, 0);
			exit(g_struct->exit_status);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status))
				g_struct->exit_status = WEXITSTATUS(status);
		}
}

void execute_pipelines(t_node **command_node, t_shell *g_struct)
{
	int status;
	int temp_fd;
	int pipes[2];
	t_node *current_node;

	if (*command_node == NULL)
		return;
	current_node = *command_node;
	temp_fd = -1;
	while (current_node)
	{
		pipes_exec(current_node, g_struct, pipes, temp_fd);
		if (temp_fd != -1)
			close(temp_fd);
		temp_fd = pipes[0];
		close(pipes[1]);
		current_node = current_node->next;
	}
	close(temp_fd);
	while (wait(NULL) > 0)
	{
	};
	free_pipes_node(command_node);
	return;
}

t_node *new_node(char **arr, t_redi_node *redirect)
{
	t_node *new;

	new = malloc(sizeof(t_node));
	new->args = arr;
	new->redirect = redirect;
	new->next = NULL;
	return (new);
}

void add_node(t_node **node, t_node *new)
{
	t_node *head;

	if (!*node)
	{
		*node = new;
		return;
	}
	head = *node;
	while (head->next)
		head = head->next;
	head->next = new;
}