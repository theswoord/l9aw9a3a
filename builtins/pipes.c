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
		printf("hh %p\n",temp);
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

void execute_pipelines(t_node **command_node, char **env, t_shell* g_struct)
{
	int i;
	int temp_fd;
	int pipes[2];
	t_node *current_node;

	if (*command_node == NULL)
		return;
	i = 0;
	current_node = *command_node;
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
			redirections(current_node->redirect);
			execute_commands_pipes(current_node->args[0], current_node->args, env,g_struct);
			exit(0);
		}
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
	// free :D
	free_pipes_node(command_node);
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

// int main(int ac, char **av, char **env)
// {
// 	t_node *command_node;

// 	command_node = NULL;

// 	char *args[] = {"ls", NULL};
// 	// char *args1[] = {"ls", NULL};
// 	// char *args2[] = {"cat", "-e", NULL};
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
// 	t_redi_node	*redirect1 = NULL;
// 	char file1[] = "text";
// 	int type1 = OUT;
// 	add_redi(&redirect1, new_redi(file1, type1));

// 	char file2[] = "tasty";
// 	int type2 = OUT;
// 	add_redi(&redirect1, new_redi(file2, type2));

// 	// t_redi_node	*redirect2 = NULL;
// 	// add_node(&command_node, new_node(args, redirect1));
// 	// char file3[] = "tasty";
// 	// int type3 = IN;
// 	// add_redi(&redirect2, new_redi(file3, type3));
// 	add_node(&command_node, new_node(args, redirect1));
// 	// add_node(&command_node, new_node(args1, NULL));

// 	// f declaration dyal linked list khod li bghiti, ya ima head_tiz w new_tiz wla rir new_command_node
// 	execute_pipelines(&command_node, env);
// 	// char *args2[] = {"ls", NULL};
// 	// char *args3[] = {"ls","-l", NULL};
// 	// add_node(&command_node, new_node(args2, NULL));
// 	// add_node(&command_node, new_node(args3, NULL));
// 	// execute_pipelines(&command_node, env);

// 	return (0);
// }