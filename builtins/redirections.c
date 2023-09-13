#include "builtins.h"

int ft_isalnum(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int find_delimeter(char *string, char *delimeter)
{
	int string_len;
	int delimeter_len;
	int i;
	int j;

	if (string == NULL || delimeter == NULL)
		return (0);
	string_len = ft_strlen(string);
	delimeter_len = ft_strlen(delimeter);
	if (delimeter_len > string_len)
		return (0);
	i = 0;
	while (i < string_len - delimeter_len)
	{
		j = 0;
		while (j < delimeter_len)
		{
			if (string[i + j] != delimeter[j])
				break;
			j++;
		}
		if (j == delimeter_len && !ft_isalnum(string[i - 1]) && string[i + delimeter_len] == '\n')
			return (1);
		i++;
	}
	// exit(0);
	return (0);
}

void redirect_into_file(ParsedCommand *data)
{
	int fd;
	int stdin_fd;
	int pid;

	fd = open("minishell_here_doc.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("open file heredoc");
		exit(1);
	}
	stdin_fd = dup(STDIN_FILENO);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 0);
		execute_commands(data->command, data->arguments, data->env);
		close(fd);
		dup2(stdin_fd, 0);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(fd);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}

void redirect_heredoc(ParsedCommand *data)
{
	int temp_fd;
	char *buffer;
	int input_len;
	int read_bytes;

	// change to tmp so it will be deleted after restarting
	temp_fd = open("minishell_here_doc.txt", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (temp_fd < 0)
	{
		perror("open file heredoc");
		exit(1);
	}
	buffer = calloc(1, 1024 + 1);
	input_len = 0;
	while (1)
	{
		read_bytes = read(0, buffer + input_len, 1024 - input_len - 1);
		if (read_bytes < 0)
			break;
		input_len += read_bytes;
		buffer[input_len] = '\0';
		if (find_delimeter(buffer, data->output_file))
			break;
	}
	write(temp_fd, buffer, input_len);
	close(temp_fd);
	free(buffer);
	redirect_into_file(data);
}

void redirect_input(ParsedCommand *data)
{
	int fd;
	int pid;
	int stdin_fd;

	fd = open(data->output_file, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		exit(1);
	}
	stdin_fd = dup(STDIN_FILENO);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, 0);
		execute_commands(data->command, data->arguments, data->env);
		close(fd);
		exit(0);
	}
	else if (pid > 0)
	{
		waitpid(pid, NULL, 0);
		close(fd);
	}
	else
	{
		perror("fork");
		exit(1);
	}
}

void ft_redirect(ParsedCommand *data)
{
	int fd;
	int pid;
	int stdout_fd;

	if (ft_strcmp(data->redirection_operator, ">") == 0)
		data->O_REDI = O_TRUNC;
	else if (ft_strcmp(data->redirection_operator, ">>") == 0)
		data->O_REDI = O_APPEND;
	else
		data->O_REDI = -1;

	if (data->O_REDI != -1)
	{
		fd = open(data->output_file, O_WRONLY | O_CREAT | data->O_REDI, 0777);
		if (fd == -1)
		{
			perror("open");
			exit(1);
		}
		stdout_fd = STDOUT_FILENO;
		pid = fork();

		if (pid == 0)
		{
			dup2(fd, 1);
			execute_commands(data->command, data->arguments, data->env);
			close(fd);
			dup2(stdout_fd, 1);
		}
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
			close(fd);
		}
		else
		{
			perror("fork");
			exit(1);
		}
	}
	else
	{
		if (ft_strcmp(data->redirection_operator, "<") == 0)
		{
			redirect_input(data);
		}
		else if (ft_strcmp(data->redirection_operator, "<<") == 0)
		{
			redirect_heredoc(data);
		}
	}
}

// int main(int ac, char **av, char **env)
// {
// 	ParsedCommand *data;

// 	data = malloc(sizeof(ParsedCommand));
// 	if (data == NULL)
// 	{
// 		perror("malloc");
// 		return 1;
// 	}
// 	data->env = env;
// 	data->command = "ls";
// 	data->redirection_operator = ">";
// 	data->output_file = "text";
// 	data->arguments = malloc(4 * sizeof(char *));
// 	data->arguments[0] = "ls";
// 	data->arguments[1] = "-l";
// 	data->arguments[2] = "-a";
// 	data->arguments[3] = "-i";
// 	data->arguments[4] = NULL;
// 	ft_redirect(data);
// 	free(data->arguments);
// 	return (0);
// }
