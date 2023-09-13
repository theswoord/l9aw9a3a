#include "builtins.h"

void execute_pipelines(array_of_commands *command_list, char **env)
{
	int i;
	int j;
	int num_pipes;
	int pipes[command_list->num_commands - 1][2];

	num_pipes = command_list->num_commands - 1;
	i = -1;
	while (++i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			printf("pipe error has occured!\n");
			return;
		}
	}
	i = 0;
	while (i < num_pipes + 1)
	{
		pid_t pid = fork();
		if (pid == 0)
		{
			if (i != 0)
			{
				close(pipes[i - 1][1]);
				dup2(pipes[i - 1][0], STDIN_FILENO);
			}

			if (i != num_pipes)
			{
				close(pipes[i][0]);
				dup2(pipes[i][1], STDOUT_FILENO);
			}

			execute_commands(command_list->commands[i].command, command_list->commands[i].args, env);
			perror(" error");
			if (i != 0)
				close(pipes[i - 1][0]);
			if (i != num_pipes)
				close(pipes[i][1]);
			exit(0);
		}
		else if (pid > 0)
		{
			if (i != 0)
			{
				close(pipes[i - 1][0]);
				close(pipes[i - 1][1]);
			}
			i++;
		}
		else
		{
			perror("fork error");
			exit(1);
		}
	}
	j = -1;
	while (++j < num_pipes)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	j = -1;
	while (++j < num_pipes + 1)
	{
		// printf("pepepeppee\n");
		if (wait(NULL) == -1)
			perror("waitpid error");
	}
	j = -1;
	while (++j < num_pipes + 1)
		free(command_list->commands[j].args);
	free(command_list->commands);
	free(command_list);
	return;
}

// int main(int ac, char **av, char **env)
// {
// 	array_of_commands *command_list;

// 	command_list = malloc(sizeof(array_of_commands));
// 	command_list->num_commands = 4;
// 	command_list->commands = (command *)malloc(command_list->num_commands * sizeof(command));

// 	command_list->commands[0].command = "ls";
// 	command_list->commands[0].args = (char **)malloc(2 * sizeof(char *));
// 	command_list->commands[0].args[0] = "ls";
// 	command_list->commands[0].args[1] = "-l";
// 	command_list->commands[0].args[2] = NULL;

// 	command_list->commands[1].command = "grep";
// 	command_list->commands[1].args = (char **)malloc(2 * sizeof(char *));
// 	command_list->commands[1].args[0] = "grep";
// 	command_list->commands[1].args[1] = "env";
// 	command_list->commands[1].args[2] = NULL;

// 	command_list->commands[2].command = "sort";
// 	command_list->commands[2].args = (char **)malloc(2 * sizeof(char *));
// 	command_list->commands[2].args[0] = "sort";
// 	command_list->commands[2].args[1] = NULL;

// 	command_list->commands[3].command = "wc";
// 	command_list->commands[3].args = (char **)malloc(3 * sizeof(char *));
// 	command_list->commands[3].args[0] = "wc";
// 	command_list->commands[3].args[1] = "-l";
// 	command_list->commands[3].args[2] = NULL;

// 	execute_pipelines(command_list, env);

// 	return (0);
// }
