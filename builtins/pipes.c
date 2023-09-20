#include "builtins.h"

void execute_pipelines(t_node *command_node, char **env)
{
	int i;
	int temp_fd;
	int pipes[2];
	t_node *current_node;

	if (command_node == NULL)
		return;
	i = 0;
	current_node = command_node;
	temp_fd = -1;
	while (current_node)
	{
		// printf("%s\n", current_node->args[0]);
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
			execute_commands(current_node->args[0], current_node->args, env);
			exit(0);
		}
		if (temp_fd != -1)
			close(temp_fd);
		temp_fd = pipes[0];
		close(pipes[1]);
		current_node = current_node->next;
	}
	close(temp_fd);
	current_node = command_node;
	while (wait(NULL) > 0) {};
	// free :D
	return;
}

t_node *new_command_node(t_node **list, char **args)
{
	t_node *node;
	int i;
	t_node *current;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		return (NULL);
	node->args = args;
	node->redirect = NULL;
	node->next = NULL;

	if (*list == NULL)
		*list = node;
	else
	{
		current = *list;
		while (current->next != NULL)
			current = current->next;
		current->next = node;
	}
	return (node);
}

t_node	*new_tiz(char **arr, t_redi_node *redirect)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->args = arr;
	new->redirect = redirect;
	new->next = NULL;
	return (new);
}

void	head_tiz(t_node **node, t_node *new)
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

// int main(int ac, char **av, char **env)
// {
// 	t_node *command_node;

// 	command_node = NULL;
	
// 	char *args[] = {"ls", "-l", NULL};
// 	char *args1[] = {"sort", NULL};
// 	char *args2[] = {"cat", "-e", NULL};

// 	// command_node.
// 	// char *args[] = {"ls", "-l", NULL};
// 	// char *args1[] = {"wc", "-l", NULL};
// 	// char *args2[] = {"cat", "-e", NULL};
// 	// you can pass the linked list directly or get the node from the return value
// 	// t_node *command1 = new_command_node(&command_node, args);

// 	// char *args2[] = {"grep", "env", NULL};
// 	// t_node *command2 = new_command_node(&command_node, args2);

// 	// char *args3[] = {"sort", NULL};
// 	// new_command_node(&command_node, args3);

// 	// char *args4[] = {"wc", "-w", NULL};
// 	// new_command_node(&command_node, args4);

// 	// char *args5[] = {"cat", "-e", NULL};
// 	// new_command_node(&command_node, args5);
// 	// command_node->*args[0]={"ls", "-l", NULL}

// 	 t_redi_node	*redirect = NULL;
// 	head_tiz(&command_node, new_tiz(args, redirect));
// 	printf("%s\n",command_node->args[0]);
// 	head_tiz(&command_node, new_tiz(args1, redirect));
// 	printf("%s\n",command_node->args[0]);
// 	head_tiz(&command_node, new_tiz(args2, redirect));
// 	printf("%s\n",command_node->args[0]);

// 	// f declaration dyal linked list khod li bghiti, ya ima head_tiz w new_tiz wla rir new_command_node
// 	execute_pipelines(command_node, env);

// 	return (0);
// }